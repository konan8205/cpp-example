/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#ifndef UNICODE
#define UNICODE
#endif
#define NOMINMAX

#pragma warning(disable : 28251)

#include <Windows.h>
#include <string>

/*
Get a unicode character from keyboard
*/

std::wstring input_str;
std::wstring input_comp;

HFONT g_hFont;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
    switch (uMsg) {
    case WM_IME_COMPOSITION: {
        input_comp.clear();

        // if the composition character is completed
        if (lParam & GCS_RESULTSTR) {
            input_str.push_back(wParam);
        }
        else {
            // GCS_COMPSTR
            input_comp.push_back(wParam);
        }
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }

    case WM_IME_ENDCOMPOSITION: {
        input_comp.clear();
        return 0;
    }

    // Get a valid character
    case WM_CHAR: {
        switch (wParam) {
        // backspace
        case 0x08: {
            if (input_str.empty()) {
                break;
            }

            // Check if the character size is 4 bytes
            if (input_str.back() >= 0xD800 && input_str.back() <= 0xDFFF &&
                input_str.size() >= 2) {
                input_str.pop_back();
            }
            input_str.pop_back();
            break;
        }
        // tab
        case 0x09:
        // linefeed
        case 0x0A:
        // carriage return
        case 0x0D:
        // escape
        case 0x1B:
            break;

        default:
            input_str.push_back(wParam);
            break;
        }

        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rectWindow;
        GetClientRect(hWnd, &rectWindow);

        // Fill the background as white
        HBRUSH brushWhite = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &rectWindow, brushWhite);

        // Print the text
        RECT rectText = rectWindow;
        rectText.left += 16;
        rectText.top += 16;
        rectText.right -= 16;
        rectText.bottom -= 16;

        SelectObject(hdc, g_hFont);

        std::wstring output_text = L"Input: " + input_str + input_comp;
        DrawTextW(hdc, output_text.data(), -1, &rectText,
                  DT_LEFT | DT_WORDBREAK);

        EndPaint(hWnd, &ps);

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
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"im_win32";

    RegisterClassW(&wc);

    HWND hWnd = CreateWindowExW(0, wc.lpszClassName, L"im_win32",
                                WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
                                CW_USEDEFAULT, CW_USEDEFAULT, 320, 240, NULL,
                                NULL, hInstance, NULL);
    if (!hWnd) {
        return 0;
    }

    g_hFont =
        CreateFontW(20, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE,
                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                    CLEARTYPE_QUALITY, FF_DONTCARE, L"Segoe UI");
    if (!g_hFont) {
        DestroyWindow(hWnd);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
