/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <cstdint>

#include <chrono>
#include <iostream>
#include <new>

std::chrono::duration<double> result[2];

int main() {
    /*
    Exception handling is EXTREMELY slow.
    Do not use it if possible.
    */

    using hrc = std::chrono::high_resolution_clock;
    hrc::time_point st, ed;

    /* if statement */
    {
        st = hrc::now();
        for (volatile int i = 0; i < 1e6; ++i) {
            if (true) {
                volatile int dummy = 0;
            }
            else {
                volatile int dummy = 1;
            }
        }

        ed = hrc::now();
        result[0] = ed - st;
    }

    /* exception */
    {
        st = hrc::now();
        for (volatile int i = 0; i < 1e6; ++i) {
            try {
                throw std::bad_alloc();
            }
            catch (const std::bad_alloc &e) {
                volatile int dummy = 0;
            }
        }

        ed = hrc::now();
        result[1] = ed - st;
    }

    // Optimize
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cout.precision(4);
    std::cout.setf(std::ios::fixed);

    // Print benchmark results
    std::cout << "if statement:             " << result[0].count() << "\n"
              << "exception:                " << result[1].count() << "\n";

    std::cout << "exception / if statement: "
              << result[1].count() / result[0].count() << "\n";

    return 0;
}
