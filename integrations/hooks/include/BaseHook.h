#ifndef CHRYSALIS_BASEHOOK_H
#define CHRYSALIS_BASEHOOK_H

#include <polyhook2/Detour/x64Detour.hpp>

#include "HooksLibraryExport.h"

// ── BaseHook ──────────────────────────────────────────────────────────
// Base class stored in the hooks map. Owns the PLH detour lifetime.
//
// IMPORTANT: hook() is NOT called in the constructor. Subclasses must call
// install() explicitly after all instance state (_instance, _address) is
// fully initialized. This prevents a race where the hooked function fires
// between _detour.hook() and the assignment of _instance.
class HOOKS BaseHook {
public:
    explicit BaseHook(uint64_t function, uint64_t hook, uint64_t* original);
    // Activate the detour. Must be called after _instance is set.
    // Returns false if polyhook could not patch the target — most
    // commonly because the function's compiled prologue is shorter than
    // the minimum bytes an x64 detour needs to overwrite (a handful of
    // bytes; trivial one-line functions under aggressive optimization
    // can fall below this). On false, NO redirection has occurred: the
    // function still runs completely untouched. The caller must not
    // proceed as though hooking succeeded — see Hook<Target>'s ctor.
    bool install();
    virtual ~BaseHook();
protected:
    PLH::x64Detour detour_;
};

#endif // CHRYSALIS_BASEHOOK_H
