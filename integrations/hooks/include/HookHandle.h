#ifndef CHRYSALIS_HOOKHANDLE_H
#define CHRYSALIS_HOOKHANDLE_H

#include <list>
#include <functional>

#include "HooksLibraryExport.h"

// =============================================================================
//  HookHandle
//  Must be defined before hook_detail so the Before/After/Replace std::function
//  signatures that reference it can be fully formed.
//
//  Returned to the caller when registering a before/after/replace callback.
//  Calling remove() schedules the callback for deletion on the next hook
//  invocation — deletion is deferred so it is safe to call remove() from
//  inside the callback itself without invalidating the iterator mid-loop.
// =============================================================================
class HOOKS HookHandle {
    friend class HooksManager;
    explicit HookHandle(std::list<std::function<void()>>& executeLater, std::function<void()> remover);
public:
    // Schedule this callback for removal. Safe to call from inside the callback.
    void remove() const;
private:
    // Raw pointer is intentional: the list is an instance member of HookBase
    // and outlives every HookHandle created during a single hook invocation.
    std::list<std::function<void()>>* executeLater_;
    std::function<void()> remover_;
};

#endif // CHRYSALIS_HOOKHANDLE_H
