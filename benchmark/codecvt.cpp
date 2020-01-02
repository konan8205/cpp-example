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

#define STR(T) \
    T##"저기 계신 저 분이 박 법학박사이시고 " \
       "여기 계신 이 분이 백 법학박사이시다."

#ifdef _WIN32
const std::wstring str = STR(L);
#else
const std::u16string str = STR(u);
#endif

std::string str_cvt;
std::chrono::duration<double> d[2];

int main() {
    /*
    codecvt is useful because it is fast enough,
    but the available character encodings are limited.
    */

    using hrc = std::chrono::high_resolution_clock;
    hrc::time_point st, ed;

    str_cvt.reserve(512);

    /* codecvt */
    {
        st = hrc::now();

#ifdef _WIN32
        using codecvt = std::codecvt<wchar_t, char, std::mbstate_t>;
        auto &f = std::use_facet<codecvt>(std::locale());
        const wchar_t *from_next;
#else
        using codecvt = std::codecvt<char16_t, char, std::mbstate_t>;
        auto &f = std::use_facet<codecvt>(std::locale());
        const char16_t *from_next;
#endif

        char *to_next;
        std::mbstate_t mb{};

        for (int i = 0; i < 1e7; ++i) {
            int size = str.size() * 4;
            str_cvt.resize(size);
            // 'str[str.size()]' is the shortest way to implement this code
            f.out(mb, &str[0], &str[str.size()], from_next, &str_cvt[0],
                  &str_cvt[size], to_next);

            // std::string does not require '\0' at the end of the string
            str_cvt.resize(to_next - &str_cvt[0]);
        }

        ed = hrc::now();
        d[0] = ed - st;
        str_cvt.clear();
    }

#ifdef _WIN32
    /* MultiByteToWideChar */
    {
        st = hrc::now();

        for (int i = 0; i < 1e7; ++i) {
            /*
            It is possible to count the number of characters.

            int size = WideCharToMultiByte(CP_UTF8, 0, (wchar_t *)str.c_str(),
                                           str.size(), NULL, 0, NULL, NULL);
            */
            int size = str.size() * 2;
            str_cvt.resize(size);

            /*
            str.data() may be require explicit declaration with Win32 API
            because some functions recongize it as 'const char *'
            */
            size =
                WideCharToMultiByte(CP_UTF8, 0, (wchar_t *)&str[0], str.size(),
                                    &str_cvt[0], str_cvt.size(), NULL, NULL);

            str_cvt.resize(size);
        }

        ed = hrc::now();
        d[1] = ed - st;
        str_cvt.clear();
    }
#else
    /* iconv */
    {
        st = hrc::now();
        iconv_t cd = iconv_open("UTF-8", "UTF-16");

        for (int i = 0; i < 1e7; ++i) {
            size_t str_size = (sizeof(char16_t) / sizeof(char)) * str.size();
            size_t str_cvt_size = str_size * 4;
            str_cvt.resize(str_cvt_size);

            char *str_ptr = (char *)(str.data());
            char *str_cvt_ptr = (char *)(str_cvt.data());
            size_t res =
                iconv(cd, &str_ptr, &str_size, &str_cvt_ptr, &str_cvt_size);
            if (res == (size_t)-1) {
                std::cerr << "iconv() error" << std::endl;
                std::exit(EXIT_FAILURE);
            }
            str_cvt.resize(str_cvt_ptr - &str_cvt[0]);
        }

        iconv_close(cd);

        ed = hrc::now();
        d[1] = ed - st;
        str_cvt.clear();
    }
#endif

    // Optimize
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cout.precision(2);
    std::cout.setf(std::ios::fixed);

    // Print benchmark results
#ifdef _WIN32
    std::cout << "codecvt:\t\t\t" << d[0].count() << std::endl
              << "WideCharToMultiByte:\t\t" << d[1].count() << std::endl
              << "codecvt/WideCharToMultiByte:\t" << d[0].count() / d[1].count()
              << std::endl;
#else
    std::cout << "codecvt:\t" << d[0].count() << std::endl
              << "iconv:\t\t" << d[1].count() << std::endl
              << "codecvt/iconv:\t" << d[0].count() / d[1].count() << std::endl;
#endif

    return 0;
}
