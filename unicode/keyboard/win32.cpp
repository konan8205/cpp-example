
#ifndef UNICODE
#define UNICODE
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#pragma warning(disable : 28251)

#include <string>

#include <Windows.h>

std::wstring input_str;
std::wstring comp_str;

/*
Get a unicode character from keyboard
*/

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
							LPARAM lParam) {
	switch (uMsg) {
	case WM_IME_COMPOSITION: {
		comp_str.clear();

		// if the composition character is completed
		if (lParam & GCS_RESULTSTR) {
			input_str.push_back(wParam);
		} else {
			// GCS_COMPSTR
			comp_str.push_back(wParam);
		}

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	}

	case WM_IME_ENDCOMPOSITION: {
		comp_str.clear();

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	}

	// Get a valid character
	case WM_CHAR: {
		switch (wParam) {
		// backspace
		case 0x08:

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

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	}

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// Fill the background as white
		HBRUSH brushWhite = CreateSolidBrush(RGB(255, 255, 255));
		RECT rectWindow;
		GetClientRect(hwnd, &rectWindow);
		FillRect(hdc, &rectWindow, brushWhite);

		// Print the text
		std::wstring output_text = L"Input: " + input_str + comp_str;
		TextOutW(hdc, 16, 16, output_text.data(), output_text.size());

		EndPaint(hwnd, &ps);

		return 0;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PWSTR pCmdLine, int nCmdShow) {
	WNDCLASSW wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"Main Window Class";

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(
		0, wc.lpszClassName, L"unicode-keyboard", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
	if (!hwnd) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}
