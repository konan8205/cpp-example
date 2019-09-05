/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <locale>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    /*
    https://docs.microsoft.com/en-us/windows/console/setconsolecp
    */
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#else
    std::locale::global(locale("en_US.UTF-8"));
#endif

    // Optimization
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cout << u8"UTF-8 is beautiful :)" << std::endl
              << u8"UTF-8は美しいです :)" << std::endl
              << u8"UTF-8은 아름답습니다 :)" << std::endl;

    return 0;
}
