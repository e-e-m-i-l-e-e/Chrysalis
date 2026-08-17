#ifndef CHRYSALIS_X64DETOUR_H
#define CHRYSALIS_X64DETOUR_H

#include <cstdint>

namespace PLH {
    class x64Detour {
    public:
        x64Detour(uint64_t fnAddress, uint64_t fnCallback, uint64_t* userTrampVar);

        bool hook();
        bool unHook();
    };
}

#endif // CHRYSALIS_X64DETOUR_H
