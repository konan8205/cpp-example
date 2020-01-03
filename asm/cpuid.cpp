/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <intrin.h>
#endif

struct cpuid_s {
    uint32_t eax, ebx, ecx, edx;
};

cpuid_s get_cpuid(uint32_t eax, uint32_t ecx = 0) {
    cpuid_s cpuInfo;

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

std::string to_bool(bool val) {
    return val == true ? "true" : "false";
}

int main() {
    // https://en.wikipedia.org/wiki/CPUID#Calling_CPUID

    cpuid_s cpuid0 = get_cpuid(0), cpuid1 = get_cpuid(1),
            cpuid7_0 = get_cpuid(7, 0), cpuid80 = get_cpuid(0x80000000),
            cpuid81 = get_cpuid(0x80000001);

    // Highest Function Parameter
    uint32_t hfp = cpuid0.eax;

    // Manufacturer ID
    char id[13];
    memcpy(id, &cpuid0.ebx, 4);
    memcpy(id + 4, &cpuid0.edx, 4);
    memcpy(id + 8, &cpuid0.ecx, 4);
    id[12] = 0;

#define format_addr \
    std::hex << std::uppercase << std::setfill('0') << std::setw(2)

    std::cout
        << "Highest Function Parameter:  0x" << format_addr << hfp
        << "\nHighest Extended Function:   0x" << cpuid80.eax
        << "\nManufacturer:                " << id
        << "\nHyper-threading:             " << to_bool(cpuid1.edx & (1 << 28))
        << "\nSSE support:                 " << to_bool(cpuid1.edx & (1 << 25))
        << "\nSSE2 support:                " << to_bool(cpuid1.edx & (1 << 26))
        << "\nSSE3 support:                " << to_bool(cpuid1.ecx & (1 << 0))
        << "\nSSSE3 support:               " << to_bool(cpuid1.ecx & (1 << 9))
        << "\nSSE4a support:               " << to_bool(cpuid81.ecx & (1 << 6))
        << "\nSSE4.1 support:              " << to_bool(cpuid1.ecx & (1 << 19))
        << "\nSSE4.2 support:              " << to_bool(cpuid1.ecx & (1 << 20))
        << "\nMMX support:                 " << to_bool(cpuid1.edx & (1 << 23))
        << "\nExtended MMX support:        " << to_bool(cpuid81.edx & (1 << 22))
        << "\nAVX support:                 " << to_bool(cpuid1.ecx & (1 << 28))
        << "\nAVX2 support:                " << to_bool(cpuid7_0.ebx & (1 << 5))
        << "\n";

    return 0;
}
