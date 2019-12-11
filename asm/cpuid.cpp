/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <cstdint>
#include <iostream>

#ifdef _WIN32
#include <intrin.h>
#endif

struct cpuid_status_s {
    uint32_t eax, ebx, ecx, edx;
};

cpuid_status_s get_cpuid(uint32_t eax, uint32_t ecx = 0) {
    cpuid_status_s cpuInfo;

#ifdef _WIN32
    __cpuidex((int *)&cpuInfo, eax, ecx);
#else
    asm volatile("cpuid"
                 : "=a"(cpuInfo.eax), "=b"(cpuInfo.ebx), "=c"(cpuInfo.ecx),
                   "=d"(cpuInfo.edx)
                 : "a"(eax), "c"(ecx));
#endif

    return cpuInfo;
}

int main() {
    // https://en.wikipedia.org/wiki/CPUID#Calling_CPUID

    cpuid_status_s cpuid1 = get_cpuid(1, 0);

    bool htt = cpuid1.edx & (1 << 28);
    bool sse2 = cpuid1.edx & (1 << 19);
    bool avx2 = get_cpuid(7, 0).ebx & (1 << 5);

    std::cout << "Hyper-threading: " << htt << std::endl
              << "SSE2 support:    " << sse2 << std::endl
              << "AVX2 support:    " << avx2 << std::endl;

    return 0;
}
