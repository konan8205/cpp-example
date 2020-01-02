/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <chrono>
#include <iostream>
#include <utility>

std::pair<int, int> p;
std::chrono::duration<double> res[3];

int main() {
    /*
    To speed up C++ STL containers like vector or deque,
    use customized allocator that reduces system call of memory allocation.
    */

    using hrc = std::chrono::high_resolution_clock;
    hrc::time_point st, ed;

    /* make_pair */
    {
        st = hrc::now();
        for (int i = 0; i < 1e8; ++i) {
            p = std::make_pair(i, i);
        }

        ed = hrc::now();
        res[0] = ed - st;
    }

    /* pair */
    {
        st = hrc::now();
        for (int i = 0; i < 1e8; ++i) {
            p = std::pair<int, int>(i, i);
        }

        ed = hrc::now();
        res[1] = ed - st;
    }

    /* native */
    {
        st = hrc::now();
        for (int i = 0; i < 1e8; ++i) {
            p.first = i, p.second = i;
        }

        ed = hrc::now();
        res[2] = ed - st;
    }

    // Optimize
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cout.precision(2);
    std::cout.setf(std::ios::fixed);

    // Print benchmark results
    std::cout << "make_pair:\t\t" << res[0].count() << "\n"
              << "pair:\t\t\t" << res[1].count() << "\n"
              << "native:\t\t\t" << res[2].count() << "\n\n";

    std::cout << "make_pair/native:\t" << res[0].count() / res[2].count()
              << "\n"
              << "pair/native:\t\t" << res[1].count() / res[2].count() << "\n";

    return 0;
}
