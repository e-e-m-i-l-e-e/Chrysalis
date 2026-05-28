#include <Windows.h>

#include "ExtensionsManager.h"

#include "PatternBuilder.h"
#include "DevToolsExtension.h"
#include "AuthenticatorExtension.h"

BOOL WINAPI DllMain(const HINSTANCE hInst, const DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);
#ifdef EXTEND_WITH_AUTHENTICATOR
        ExtensionsManager::addExtension(new AuthenticatorExtension());
#endif
#ifdef EXTEND_WITH_PATTERN_BUILDER
        ExtensionsManager::addExtension(new PatternBuilder());
#endif
#ifdef EXTEND_WITH_DEV_TOOLS
        ExtensionsManager::addExtension(DevToolsExtension::create());
#endif
        ExtensionsManager::install();
    }
    return TRUE;
}
