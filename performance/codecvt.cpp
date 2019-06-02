/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <chrono>
#include <iostream>
#include <limits>
#include <locale>
#include <string>

#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <iconv.h>
#endif

using namespace std;
using namespace std::chrono;

#define STR(T) T##"저기 계신 저 분이 박 법학박사이시고 여기 계신 이 분이 백 법학박사이시다."

#ifdef _WIN32
wstring str = STR(L);
#else
u16string str = STR(u);
#endif
string str_cvt;
duration<double> d[2];

int main()
{
	/*
	codecvt is useful because it is fast enough,
	but the available character encodings are limited.
	*/
	high_resolution_clock::time_point st, ed;

	/* codecvt */
	st = high_resolution_clock::now();

#ifdef _WIN32
	auto &f = use_facet<codecvt<wchar_t, char, mbstate_t>>(locale());
	const wchar_t *from_next;
#else
	auto &f = use_facet<codecvt<char16_t, char, mbstate_t>>(locale());
	const char16_t *from_next;
#endif
	char *to_next;
	mbstate_t mb{};

	for (int i = 0; i < 1e7; ++i) {
		int size = str.size() * 2;
		str_cvt.resize(size);
		// 'str[str.size()]' is the shortest way to implement this code
		f.out(mb, &str[0], &str[str.size()], from_next, &str_cvt[0], &str_cvt[size], to_next);
		str_cvt.resize(to_next - &str_cvt[0]);
	}

	ed = high_resolution_clock::now();
	d[0] = ed - st;
	str_cvt.clear();

#ifdef _WIN32
	/* MultiByteToWideChar */
	st = high_resolution_clock::now();

	for (int i = 0; i < 1e7; ++i) {
		//int size = WideCharToMultiByte(CP_UTF8, 0, (wchar_t *)str.c_str(), str.size(), NULL, 0, NULL, NULL);
		int size = str.size() * 2;
		str_cvt.resize(size);
		/*
		str.data() may be require explicit declaration with Win32 API
		because some functions recongize it as 'const char *'
		*/
		size = WideCharToMultiByte(CP_UTF8, 0, (wchar_t *)str.c_str(), str.size(), &str_cvt[0], str_cvt.size(), NULL, NULL);
		str_cvt.resize(size);
	}

	ed = high_resolution_clock::now();
	d[1] = ed - st;
	str_cvt.clear();

#else
	/* iconv */
	st = high_resolution_clock::now();
	iconv_t cd = iconv_open("UTF-8", "UTF-16");

	for (int i = 0; i < 1e7; ++i) {
		size_t str_size = (sizeof(char16_t) / sizeof(char)) * str.size();
		size_t str_cvt_size = str_size * 4;
		str_cvt.resize(str_cvt_size);

		char *str_ptr = (char *)(str.data());
		char *str_cvt_ptr = (char *)(str_cvt.data());
		str_cvt_size = iconv(cd, &str_ptr, &str_size, &str_cvt_ptr, &str_cvt_size);
		if (str_cvt_size == -1) {
			exit(EXIT_FAILURE);
		}
		str_cvt.resize(str_cvt_size);
	}

	iconv_close(cd);

	ed = high_resolution_clock::now();
	d[1] = ed - st;
	str_cvt.clear();

#endif

	/* print all results */

	// Optimization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout.precision(2);
	cout.setf(ios::fixed);

#ifdef _WIN32
	cout << "codecvt:\t\t\t" << d[0].count() << endl
	     << "WideCharToMultiByte:\t\t" << d[1].count() << endl
	     << "codecvt/WideCharToMultiByte:\t" << d[0].count() / d[1].count() << endl;
#else
	cout << "codecvt:\t" << d[0].count() << endl
	     << "iconv:\t\t" << d[1].count() << endl
	     << "codecvt/iconv:\t" << d[0].count() / d[1].count() << endl;
#endif

	return 0;
}