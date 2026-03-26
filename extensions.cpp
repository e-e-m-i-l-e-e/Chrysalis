#include <Windows.h>
#include <HooksManager.h>

#include "ExtensionsManager.h"

#ifdef SAMPLES_EXTENSION
#include "SamplesExtension.h"
#endif

BOOL WINAPI DllMain(HINSTANCE hInst, const DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);

#ifdef SAMPLES_EXTENSION
        new SamplesExtension();
#endif

        ExtensionsManager::install();
    }
    return TRUE;
}
