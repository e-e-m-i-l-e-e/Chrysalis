#include "BaseHook.h"

BaseHook::BaseHook(const uint64_t function, const uint64_t hook, uint64_t* original)
    :detour_(function, hook, original) {}

bool BaseHook::install() {
    return detour_.hook();
}

BaseHook::~BaseHook() {
    detour_.unHook();
}
