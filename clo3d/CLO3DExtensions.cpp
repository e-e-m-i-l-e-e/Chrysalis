#include <Windows.h>

#include "ExtensionsManager.h"

#include "PatternBuilder.h"
#include "AuthenticatorExtension.h"

BOOL WINAPI DllMain(HINSTANCE hInst, const DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);
#ifdef EXTEND_WITH_AUTHENTICATOR
        ExtensionsManager::registerExtension(new AuthenticatorExtension());
#endif
#ifdef EXTEND_WITH_PATTERN_BUILDER
        ExtensionsManager::registerExtension(new PatternBuilder());
#endif
        ExtensionsManager::install();
    }
    return TRUE;
}
