/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>

std::chrono::duration<double> result[6];
const std::int64_t test_size = 1024 * 1024 * 4;
const std::int64_t test_case = 16;

int main() {
    /*
    Good ways to reallocate memory:
    1. If you need to keep your data, use realloc(). It's ~4 times faster than
       using malloc()/free() and copying your data when scaling up. When scaling
       down it is 10,000-100,000 times faster. NEVER copy stuff manually.
    2. If you don't need to keep your data, you should use malloc()/free() to
       scale up (increasing memory size) but use realloc() when scaling down
       (reducing memory size).
    3. If you don't know the previous size (you don't know wether you're scaling
       down or up), use malloc()/free(). When scaling down, realloc() is ~40
       times faster, but when scaling up, realloc() is ~7600 times slower.
       Unless your program does a few huge allocations and tons of little
       deallocations (~200 times more deallocations than allocations, which can
       be possible), you should use malloc()/free().

    https://stackoverflow.com/questions/1401234
    */

    using hrc = std::chrono::high_resolution_clock;
    hrc::time_point st, ed;

    // Increasing memory with lossful malloc
    {
        int *ptr = (int *)std::malloc(test_size);
        [[unlikely]] if (ptr == nullptr) {
            std::exit(1);
        }
        st = hrc::now();

        for (int i = 2; i <= test_case; ++i) {
            std::free(ptr);
            ptr = (int *)std::malloc(test_size * i);
            [[unlikely]] if (ptr == nullptr) {
                std::exit(1);
            }
        }

        ed = hrc::now();
        result[0] = ed - st;

        free(ptr);
    }

    // Increasing memory with malloc & memcpy
    {
        int *ptr = (int *)std::malloc(test_size);
        [[unlikely]] if (ptr == nullptr) {
            std::exit(1);
        }
        st = hrc::now();

        for (int i = 2; i <= test_case; ++i) {
            int *copy = (int *)std::malloc(test_size * i);
            [[unlikely]] if (copy == nullptr) {
                std::exit(1);
            }
            std::memcpy(copy, ptr, test_size * (i - 1));
            std::free(ptr);
            ptr = copy;
        }

        ed = hrc::now();
        result[1] = ed - st;

        std::free(ptr);
    }

    // Increasing memory with realloc
    {
        int *ptr = (int *)std::malloc(test_size);
        [[unlikely]] if (ptr == nullptr) {
            std::exit(1);
        }
        st = hrc::now();

        for (int i = 2; i <= test_case; ++i) {
            int *ret = (int *)std::realloc(ptr, test_size * i);
            [[unlikely]] if (ret == nullptr) {
                std::exit(1);
            }
            ptr = ret;
        }

        ed = hrc::now();
        result[2] = ed - st;

        std::free(ptr);
    }

    // Decreasing memory with lossful malloc
    {
        int *ptr = (int *)std::malloc(test_size * test_case);
        [[unlikely]] if (ptr == nullptr) {
            std::exit(1);
        }
        st = hrc::now();

        for (int i = test_case - 1; i >= 1; --i) {
            std::free(ptr);
            ptr = (int *)std::malloc(test_size * i);
            [[unlikely]] if (ptr == nullptr) {
                std::exit(1);
            }
        }

        ed = hrc::now();
        result[3] = ed - st;

        free(ptr);
    }

    // Decreasing memory with malloc & memcpy
    {
        int *ptr = (int *)std::malloc(test_size * test_case);
        [[unlikely]] if (ptr == nullptr) {
            std::exit(1);
        }
        st = hrc::now();

        for (int i = test_case - 1; i >= 1; --i) {
            int *copy = (int *)std::malloc(test_size * i);
            [[unlikely]] if (copy == nullptr) {
                std::exit(1);
            }
            std::memcpy(copy, ptr, test_size * i);
            std::free(ptr);
            ptr = copy;
        }

        ed = hrc::now();
        result[4] = ed - st;

        std::free(ptr);
    }

    // Decreasing memory with realloc
    {
        int *ptr = (int *)std::malloc(test_size * test_case);
        [[unlikely]] if (ptr == nullptr) {
            std::exit(1);
        }
        st = hrc::now();

        for (int i = test_case - 1; i >= 1; --i) {
            int *ret = (int *)std::realloc(ptr, test_size * i);
            [[unlikely]] if (ret == nullptr) {
                std::exit(1);
            }
            ptr = ret;
        }

        ed = hrc::now();
        result[5] = ed - st;

        std::free(ptr);
    }

    // Optimize
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cout.precision(6);
    std::cout.setf(std::ios::fixed);

    // Print benchmark results
    std::cout << "Increasing memory with\n"
              << "lossful malloc:  " << result[0].count() << "\n"
              << "malloc & memcpy: " << result[1].count() << "\n"
              << "realloc:         " << result[2].count() << "\n\n";

    std::cout << "Decreasing memory with\n"
              << "lossful malloc:  " << result[3].count() << "\n"
              << "malloc & memcpy: " << result[4].count() << "\n"
              << "realloc:         " << result[5].count() << "\n\n";

    return 0;
}
