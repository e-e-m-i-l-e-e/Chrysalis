#include "BaseConsoleUser.h"

#include <cstdio>
#ifdef _WIN32
    #include "Windows.h"
#endif

using namespace Logging;

BaseConsoleUser::BaseConsoleUser() {
#ifdef _WIN32
    const bool attached = AttachConsole(ATTACH_PARENT_PROCESS);
    if (const bool allocated = !attached && AllocConsole(); attached || allocated) {
        FILE* f = nullptr;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONOUT$", "w", stderr);
    }

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    auto enableVT = [](const DWORD stdHandle)
    {
        const HANDLE h = GetStdHandle(stdHandle);
        if (h == INVALID_HANDLE_VALUE) return;
        DWORD mode = 0;
        if (GetConsoleMode(h, &mode)) SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    };
    enableVT(STD_OUTPUT_HANDLE);
    enableVT(STD_ERROR_HANDLE);
#endif
}
