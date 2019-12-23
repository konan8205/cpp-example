/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#ifndef UNICODE
#define UNICODE
#endif
#define NOMINMAX

#include <Windows.h>

#include <cstdint>
#include <sstream>
#include <string>

/*
Add support for HiDPI in Win32
*/

struct window_s {
    wchar_t *name;
    int32_t width, height;
    uint32_t style;
    COLORREF background;
};

constexpr window_s text_window = {
    (wchar_t *)L"hd_win32",
    320,
    240,
    WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
    RGB(255, 255, 255),
};

float text_window_scale = 1.f;

float UpdateWindowScale(HWND hWnd, window_s info) {

    DWORD dwStyle = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
    if (!dwStyle) {
        return 0.f;
    }

    DWORD dwExStyle = (DWORD)GetWindowLong(hWnd, GWL_EXSTYLE);
    if (!dwExStyle) {
        return 0.f;
    }

    UINT dpi = GetDpiForWindow(hWnd);
    if (!dpi) {
        return 0.f;
    }

    float scale = dpi / 96.f;
    RECT scaledRect = {0, 0, (LONG)(info.width * scale),
                       (LONG)(info.height * scale)};

    if (!AdjustWindowRectExForDpi(&scaledRect, dwStyle, FALSE, dwExStyle,
                                  dpi)) {
        return 0.f;
    }

    if (!SetWindowPos(hWnd, NULL, 0, 0, scaledRect.right - scaledRect.left,
                      scaledRect.bottom - scaledRect.top,
                      SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE)) {
        return FALSE;
    }

    return scale;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rectWindow;
        GetClientRect(hWnd, &rectWindow);

        HFONT hFont = CreateFontW(20 * text_window_scale, 0, 0, 0, FW_REGULAR,
                                  FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                  CLEARTYPE_QUALITY, FF_DONTCARE, L"Segoe UI");
        if (!hFont) {
            ExitProcess(1);
            return 0;
        }

        SelectObject(hdc, hFont);

        RECT rectText = rectWindow;
        UINT padding = 16 * text_window_scale;
        rectText.left += padding;
        rectText.top += padding;
        rectText.right -= padding;
        rectText.bottom -= padding;

        std::wstringstream stream;
        stream << L"DPI: " << GetDpiForWindow(hWnd) << L" / Scale: "
               << text_window_scale;

        DrawTextW(hdc, stream.str().data(), -1, &rectText,
                  DT_LEFT | DT_WORDBREAK);

        DeleteObject(hFont);

        EndPaint(hWnd, &ps);

        return 0;
    }

    case WM_DPICHANGED: {
        text_window_scale = UpdateWindowScale(hWnd, text_window);
        if (!text_window_scale || !InvalidateRect(hWnd, NULL, TRUE)) {
            ExitProcess(1);
        }
        return 0;
    }

    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
    if (!SetThreadDpiAwarenessContext(
            DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
        return 1;
    }

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = text_window.name;
    wc.hbrBackground = CreateSolidBrush(text_window.background);

    RegisterClassW(&wc);

    HWND hWnd = CreateWindowExW(0, wc.lpszClassName, text_window.name,
                                text_window.style, CW_USEDEFAULT, CW_USEDEFAULT,
                                text_window.width, text_window.height, NULL,
                                NULL, hInstance, NULL);
    if (!hWnd) {
        return 1;
    }

    text_window_scale = UpdateWindowScale(hWnd, text_window);
    if (!text_window_scale) {
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    DeleteObject(wc.hbrBackground);

    return 0;
}
