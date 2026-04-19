#include <Windows.h>
#include <HooksManager.h>

#include "ExtensionsManager.h"
#include "PatternBuilder.h"

BOOL WINAPI DllMain(HINSTANCE hInst, const DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);
        ExtensionsManager::registerExtension(new PatternBuilder());
        ExtensionsManager::install();
    }
    return TRUE;
}
