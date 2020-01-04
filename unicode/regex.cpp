/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <iostream>
#include <locale>
#include <regex>
#include <string>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#endif

// The default flag for regex is to use ECMAScript
#define STR(T) \
    T##"내가 그린 기린 그림은 잘 그린 기린 그림이고 " \
       "네가 그린 기린 그림은 잘 못 그린 기린 그림이다."
#define STR_REPLACE(T) T##"하마 그림은 이것"
#define STR_REGEX(T) T##"기린 .* 그림"

#ifdef _WIN32
// In Windows, there is no way to use regex with UTF-8 directly.
std::wstring str = STR(L);
const std::wstring str_replace = STR_REPLACE(L);
const std::wregex str_regex(STR_REGEX(L));

#else
std::string str = STR(u8);
const std::string str_replace = STR_REPLACE(u8);
const std::regex str_regex(STR_REGEX(u8));

#endif

int main() {
    // Optimization
    std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
    std::wcin.tie(NULL);
    std::wcout.tie(NULL);
#else
    std::cin.tie(NULL);
    std::cout.tie(NULL);
#endif

#ifdef _WIN32
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    std::wcout << str << std::endl;
    str = std::regex_replace(str, str_regex, str_replace);
    std::wcout << str << std::endl;
#else
    std::locale::global(std::locale("en_US.UTF-8"));

    std::cout << str << std::endl;
    str = std::regex_replace(str, str_regex, str_replace);
    std::cout << str << std::endl;
#endif

    return 0;
}
