/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <chrono>
#include <iostream>
#include <string>

#include <cstdio>

std::string str = "abcdefghijklnmopqrstuvwxyz";
std::chrono::duration<double> t[4];

int main() {
    /*
    If you set ios_base::sync_with_stdio(false),
    std::cout is fast enough.
    */

    using hrc = std::chrono::high_resolution_clock;
    hrc::time_point st, ed;

    /* cout */
    {
        std::cout.flush();
        st = hrc::now();
        for (int i = 0; i < 1e4; ++i) {
            std::cout << str << std::endl;
        }

        ed = hrc::now();
        t[0] = ed - st;
    }

    /* cout optimized */
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);

        std::cout.flush();
        st = hrc::now();
        for (int i = 0; i < 1e4; ++i) {
            std::cout << str << std::endl;
        }

        ed = hrc::now();
        t[1] = ed - st;
    }

    // Prepare for C functions
    std::cout.flush();
    std::ios_base::sync_with_stdio(true);

    /* printf */
    {
        std::fflush(stdout);
        st = hrc::now();
        for (int i = 0; i < 1e4; ++i) {
            std::printf("%s\n", str.data());
        }

        ed = hrc::now();
        t[2] = ed - st;
    }

    /* puts */
    {
        std::fflush(stdout);
        st = hrc::now();
        for (int i = 0; i < 1e4; ++i) {
            std::puts(str.data());
        }

        ed = hrc::now();
        t[3] = ed - st;
    }

    // Optimize
    std::ios_base::sync_with_stdio(false);

    std::cout.precision(2);
    std::cout.setf(std::ios::fixed);

#if _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    // Print benchmark results
    std::cout << "\n"
              << "cout:\t\t\t" << t[0].count() << "\n"
              << "cout optimized:\t\t" << t[1].count() << "\n"
              << "printf:\t\t\t" << t[2].count() << "\n"
              << "puts:\t\t\t" << t[3].count() << "\n\n";

    std::cout << "cout/printf:\t\t" << t[0].count() / t[2].count() << "\n"
              << "cout optimized/printf:\t" << t[1].count() / t[2].count()
              << "\n"
              << "puts/printf:\t\t" << t[2].count() / t[3].count() << "\n";

    return 0;
}
