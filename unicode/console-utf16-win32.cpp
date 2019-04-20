/*
    Shinwoo Park
    natural7530@gmail.com
    
    MIT License
*/

#include <iostream>

#include <windows.h>
#include <io.h>

#ifndef _O_U16TEXT
#define _O_U16TEXT 0x00020000
#endif // _O_U16TEXT

using namespace std;

wchar_t str[3][64] =
	{
		L"UTF-16 is useful :)\n",
		L"UTF-16は有用です :)\n",
		L"UTF-16은 유용합니다 :)\n",
};

inline void putws_win32(wchar_t *str)
{
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str, wcslen(str), NULL, NULL);
}

int main()
{
	/*
	Using Win32 API Unicode Functions,
	Handling Unicode is simple, but only available on Windows.
	*/

	// Method 1: These are example of using WriteConsoleW.
	for (auto iter : str)
	{
		putws_win32(iter);
	}
	putws_win32(L"\n");

	/*
	If you want to use wcout or wprintf on all available Unicode ranges,
	Set the file translation mode of stdout as Unicode.

	Note:
	You must use only UTF-16 printing functions.
	The difference of _O_U16TEXT and _O_U8TEXT is only input/output encoding.

	Reference:
	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode
	https://stackoverflow.com/questions/45232484
	*/
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	// Optimization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// Method 2: This is example of using wcout.
	for (auto iter : str)
	{
		wcout << iter;
	}
	wcout << endl;

	return 0;
}
