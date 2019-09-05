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

    using high_resolution_clock = std::chrono::high_resolution_clock;
    high_resolution_clock::time_point st, ed;

    // cout
    {
        std::cout.flush();
        st = high_resolution_clock::now();
        for (int i = 0; i < 1e4; ++i) {
            std::cout << str << std::endl;
        }

        ed = high_resolution_clock::now();
        t[0] = ed - st;
    }

    // cout optimized
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);

        std::cout.flush();
        st = high_resolution_clock::now();
        for (int i = 0; i < 1e4; ++i) {
            std::cout << str << std::endl;
        }

        ed = high_resolution_clock::now();
        t[1] = ed - st;
    }

    // prepare for c functions
    std::ios_base::sync_with_stdio(true);

    // printf
    {
        std::fflush(stdout);
        st = high_resolution_clock::now();
        for (int i = 0; i < 1e4; ++i) {
            std::printf("%s\n", str.data());
        }

        ed = high_resolution_clock::now();
        t[2] = ed - st;
    }

    // puts
    {
        std::fflush(stdout);
        st = high_resolution_clock::now();
        for (int i = 0; i < 1e4; ++i) {
            std::puts(str.data());
        }

        ed = high_resolution_clock::now();
        t[3] = ed - st;
    }

    /* print all results */

    // Optimization
    std::ios_base::sync_with_stdio(false);

    std::cout.precision(2);
    std::cout.setf(std::ios::fixed);

    std::cout.flush();

#if _WIN32
    std::system("cls");
#else
    std::system("clear; clear");
#endif

    std::cout << std::endl
              << "cout:\t\t\t" << t[0].count() << std::endl
              << "cout optimized:\t\t" << t[1].count() << std::endl
              << "printf:\t\t\t" << t[2].count() << std::endl
              << "puts:\t\t\t" << t[3].count() << std::endl
              << std::endl;
    std::cout << "cout/printf:\t\t" << t[0].count() / t[2].count() << std::endl
              << "cout optimized/printf:\t" << t[1].count() / t[2].count()
              << std::endl
              << "puts/printf:\t\t" << t[2].count() / t[3].count() << std::endl;

    return 0;
}
