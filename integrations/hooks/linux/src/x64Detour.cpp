#include "x64Detour.h"

using namespace PLH;

x64Detour::x64Detour(uint64_t fnAddress, uint64_t fnCallback, uint64_t* userTrampVar) {}

bool x64Detour::hook() {
    return true;
}

bool x64Detour::unHook() {
    return true;
}
