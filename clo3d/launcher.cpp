#define LOGGER_NAME "Launcher"

#include <Windows.h>
#include <Logger.h>

// =============================================================================
//  RAII handle wrapper
//  Automatically closes a Win32 HANDLE on scope exit, preventing leaks even
//  when early-return paths are taken on error.
// =============================================================================
struct WinHandle
{
    explicit WinHandle(HANDLE h = nullptr) : h(h) {}
    ~WinHandle() { if (h && h != INVALID_HANDLE_VALUE) CloseHandle(h); }

    // Non-copyable — ownership is unique.
    WinHandle(const WinHandle&)            = delete;
    WinHandle& operator=(const WinHandle&) = delete;

    // Movable so it can be returned from factory functions.
    WinHandle(WinHandle&& o) noexcept : h(o.h) { o.h = nullptr; }

    explicit operator bool() const { return h && h != INVALID_HANDLE_VALUE; }
    operator HANDLE()        const { return h; }

    HANDLE h;
};

// =============================================================================
//  lastErrorMessage
//  Formats the last Win32 error code as a human-readable string, giving far
//  more context than a bare "function failed" message.
// =============================================================================
static std::string lastErrorMessage();

// =============================================================================
//  injectDll
//  Injects a DLL into an already-created (suspended) target process by:
//    1. Allocating a page of memory in the target for the DLL path string
//    2. Writing the path into it
//    3. Spawning a remote thread that calls LoadLibraryA with that address
//
//  The remote memory is freed and the thread handle closed before returning,
//  regardless of outcome.
// =============================================================================
static bool injectDll(HANDLE process, const std::string& dllPath);

// =============================================================================
//  createKillOnCloseJob
//  Creates a Windows Job Object configured so that all child processes are
//  terminated automatically when our launcher process exits — preventing
//  orphaned CLO3D processes if the launcher is force-killed.
// =============================================================================
static WinHandle createKillOnCloseJob();

int main() {
    const std::string dllPath = std::string(CLO_HOME) + "/Extensions.dll";
    const std::string targetExe = std::string(CLO_HOME) + "/CLO_Standalone_OnlineAuth_x64.exe";

    LOG_INFO("Launcher starting");
    LOG_INFO("Target : {}", targetExe);
    LOG_INFO("DLL    : {}", dllPath);

    // ── Job object — ensures CLO3D dies with the launcher ─────────────────────
    const WinHandle job = createKillOnCloseJob();
    if (!job) {
        LOG_CRITICAL("Failed to create job object — aborting");
        return 1;
    }

    // ── Launch CLO3D suspended so we can inject before any code runs ──────────
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    if (!CreateProcessA(targetExe.c_str(), nullptr, nullptr, nullptr,
                        FALSE, CREATE_SUSPENDED, nullptr, nullptr, &si, &pi)) {
        LOG_CRITICAL("CreateProcessA failed: {}", lastErrorMessage());
        return 1;
    }

    // Wrap handles immediately so they are closed on any exit path.
    const WinHandle process{pi.hProcess};
    const WinHandle mainThread{pi.hThread};

    LOG_INFO("CLO3D process created (PID {})", pi.dwProcessId);

    // Attach to job so the child is killed if this launcher exits.
    AssignProcessToJobObject(job, process);

    // ── Inject the extension DLL ───────────────────────────────────────────────
    if (!injectDll(process, dllPath)) {
        LOG_CRITICAL("DLL injection failed — terminating CLO3D");
        TerminateProcess(process, 1);
        return 1;
    }

    LOG_INFO("DLL injected successfully — resuming CLO3D");
    ResumeThread(mainThread);

    // ── Wait for CLO3D to exit ─────────────────────────────────────────────────
    WaitForSingleObject(process, INFINITE);

    DWORD exitCode = 0;
    GetExitCodeProcess(process, &exitCode);
    LOG_INFO("CLO3D exited with code {}", exitCode);

    return static_cast<int>(exitCode);
}

static std::string lastErrorMessage() {
    const DWORD code = GetLastError();
    char *buf = nullptr;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&buf), 0, nullptr);

    std::string msg = buf ? buf : "unknown error";
    if (buf) LocalFree(buf);

    // Strip the trailing \r\n FormatMessage appends
    while (!msg.empty() && (msg.back() == '\n' || msg.back() == '\r'))
        msg.pop_back();

    return msg + " (0x" + [code] {
        char hex[16];
        snprintf(hex, sizeof(hex), "%08X", code);
        return std::string(hex);
    }() + ")";
}

static bool injectDll(const HANDLE process, const std::string &dllPath) {
    const SIZE_T pathSize = dllPath.size() + 1; // include null terminator

    // ── Allocate a page in the target process ─────────────────────────────────
    const LPVOID remoteMem = VirtualAllocEx(process, nullptr, pathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (!remoteMem) {
        LOG_ERROR("VirtualAllocEx failed: {}", lastErrorMessage());
        return false;
    }

    // Ensure remote memory is freed even if later steps fail.
    // Lambda captures so the address is available at cleanup time.
    const auto freeRemote = [&] { VirtualFreeEx(process, remoteMem, 0, MEM_RELEASE); };

    // ── Write the DLL path into target memory ─────────────────────────────────
    if (!WriteProcessMemory(process, remoteMem, dllPath.c_str(), pathSize, nullptr)) {
        LOG_ERROR("WriteProcessMemory failed: {}", lastErrorMessage());
        freeRemote();
        return false;
    }

    // ── Spawn a remote thread to call LoadLibraryA ────────────────────────────
    // GetProcAddress is used instead of a direct cast to LoadLibraryA to ensure
    // we get the exact runtime address of the function in the target process
    // (safe on all modern x64 Windows since kernel32 is mapped at the same
    // virtual address in every process).
    const auto loadLibAddr = reinterpret_cast<LPTHREAD_START_ROUTINE>(
        GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"));

    const WinHandle thread{
        CreateRemoteThread(
            process, nullptr, 0, loadLibAddr, remoteMem, 0, nullptr)
    };

    if (!thread) {
        LOG_ERROR("CreateRemoteThread failed: {}", lastErrorMessage());
        freeRemote();
        return false;
    }

    WaitForSingleObject(thread, INFINITE);

    DWORD moduleBase = 0;
    GetExitCodeThread(thread, &moduleBase);

    freeRemote();

    if (!moduleBase) {
        LOG_ERROR("LoadLibraryA returned NULL — DLL failed to load");
        return false;
    }

    LOG_INFO("DLL loaded at base address 0x{:08X}", moduleBase);
    return true;
}

static WinHandle createKillOnCloseJob() {
    WinHandle job{CreateJobObjectA(nullptr, nullptr)};
    if (!job) {
        LOG_ERROR("CreateJobObjectA failed: {}", lastErrorMessage());
        return WinHandle{};
    }

    JOBOBJECT_EXTENDED_LIMIT_INFORMATION info{};
    info.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;

    if (!SetInformationJobObject(job, JobObjectExtendedLimitInformation,
                                 &info, sizeof(info))) {
        LOG_ERROR("SetInformationJobObject failed: {}", lastErrorMessage());
        return WinHandle{};
    }

    return job;
}
