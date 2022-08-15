#include "utils.h"

utilities g_utils;

uintptr_t utilities::signature(const std::string& signature) {
    uintptr_t moduleAdressmm = 0;
    moduleAdressmm = (uintptr_t)GetModuleHandleA(NULL);

    static auto patternToByteZmm = [](const char* pattern) {
        auto       bytesmm = std::vector<int>{};
        const auto startmm = const_cast<char*>(pattern);
        const auto endmm = const_cast<char*>(pattern) + strlen(pattern);

        for (auto currentmm = startmm; currentmm < endmm; ++currentmm) {
            if (*currentmm == '?') {
                ++currentmm;
                if (*currentmm == '?')
                    ++currentmm;
                bytesmm.push_back(-1);
            }
            else { bytesmm.push_back(strtoul(currentmm, &currentmm, 16)); }
        }
        return bytesmm;
    };

    const auto dosHeadermm = (PIMAGE_DOS_HEADER)moduleAdressmm;
    const auto ntHeadersmm = (PIMAGE_NT_HEADERS)((std::uint8_t*)moduleAdressmm + dosHeadermm->e_lfanew);

    const auto sizeOfImage = ntHeadersmm->OptionalHeader.SizeOfImage;
    auto       patternBytesmm = patternToByteZmm(signature.c_str());
    const auto scanBytesmm = reinterpret_cast<std::uint8_t*>(moduleAdressmm);

    const auto smm = patternBytesmm.size();
    const auto dmm = patternBytesmm.data();

    for (auto imm = 0ul; imm < sizeOfImage - smm; ++imm) {
        bool foundmm = true;
        for (auto jmm = 0ul; jmm < smm; ++jmm) {
            if (scanBytesmm[imm + jmm] != dmm[jmm] && dmm[jmm] != -1) {
                foundmm = false;
                break;
            }
        }
        if (foundmm) { return reinterpret_cast<uintptr_t>(&scanBytesmm[imm]); }
    }
    return NULL;
}