/*
    Shinwoo Park
    natural7530@gmail.com

    MIT License
*/

#include <iostream>
#include <locale>
#include <regex>
#include <string>

#ifdef _WIN32
#include <io.h>
#include <windows.h>

#ifndef _O_U16TEXT
#define _O_U16TEXT 0x00020000
#endif // _O_U16TEXT
#endif // _WIN32

using namespace std;

#define STR(T) T##"내가 그린 기린 그림은 잘 그린 기린 그림이고 네가 그린 기린 그림은 잘 못 그린 기린 그림이다."
#define STR_REPLACE(T) T##"하마 그림"
#define STR_REGEX(T) T##"기린 .* 그림"

#ifdef _WIN32
// In Windows, there is no way to use regex with UTF-8 directly.
wstring str = STR(L);
wstring str_replace = STR_REPLACE(L);
wregex str_regex(STR_REGEX(L));
#else
string str = STR(u8);
string str_replace = STR_REPLACE(u8);
regex str_regex(STR_REGEX(u8));
#endif // _WIN32

int main()
{
	// Optimization
	ios_base::sync_with_stdio(false);
#ifdef _WIN32
	wcin.tie(NULL);
	wcout.tie(NULL);
#else
	cin.tie(NULL);
	cout.tie(NULL);
#endif // _WIN32

#ifdef _WIN32
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	wcout << str << endl;
	str = regex_replace(str, str_regex, str_replace);
	wcout << str << endl;
#else
	locale::global(locale("en_US.UTF-8"));

	cout << str << endl;
	str = regex_replace(str, str_regex, str_replace);
	cout << str << endl;
#endif // _WIN32

	return 0;
}
