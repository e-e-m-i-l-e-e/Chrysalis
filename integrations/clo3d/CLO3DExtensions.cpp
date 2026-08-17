#include <Windows.h>

#include <filesystem>

#include "ExtensionsManager.h"
#include "Logging.h"
#define LOGGER_NAME "CLO3DExtensions"

#include <string>

#include "CLO3DExtensionExport.h"

class BaseExtension;

// Loads a plugin DLL (Chrysalis/Authenticator/DevTools/...) and returns the
// BaseExtension it creates. A plugin that fails to load or is missing its
// expected exports is logged and skipped - it must never take down the rest
// of CLO3D's extension loading.
class CLO3D_EXTENSION ExtensionLoader {
public:
    // Returns a heap-allocated BaseExtension owned by the caller, or nullptr
    // if the DLL could not be loaded or does not export createExtension().
    static BaseExtension* load(const std::wstring& dllPath);
};

class BaseExtension;

// ABI contract every plugin DLL (ChrysalisExtension.dll, AuthenticatorExtension.dll,
// DevToolsExtension.dll, ...) must implement, and ExtensionLoader relies on.
//
// createExtension(): heap-allocates and returns a new BaseExtension - ownership
// passes to the caller.
// destroyExtension(): must be used to free anything returned by createExtension().
// Allocation and deallocation both happen inside the plugin's own module, avoiding
// the cross-DLL heap/CRT mismatch that comes from allocating in one module and
// calling plain `delete` in another.

constexpr auto CREATE_EXTENSION_SYMBOL = "create";

namespace {
    std::filesystem::path extensionDirectory(const HINSTANCE hInst) {
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(hInst, path, MAX_PATH);
        return std::filesystem::path(path).parent_path() / "extensions";
    }

    void loadAllExtensions(const std::filesystem::path& directory) {
        std::error_code error;
        // Non-throwing overload deliberately - directory_iterator's throwing
        // constructor would propagate an exception out of DllMain if the
        // folder is missing, which is unsafe to let happen at this point.
        const auto iterator = std::filesystem::directory_iterator(directory, error);
        if (error) {
            LOG_ERROR("Extension directory not found or unreadable: {} ({})",
                       directory.string(), error.message());
            return;
        }

        for (const auto& entry: iterator) {
            if (!entry.is_regular_file(error) || error) continue;

            auto extension = entry.path().extension().wstring();
            std::ranges::transform(extension, extension.begin(), ::towlower);
            if (extension != L".dll") continue;

            if (auto* loaded = ExtensionLoader::load(entry.path().wstring())) {
                ExtensionsManager::addExtension(loaded);
            }
            // A single failed/malformed plugin is logged and skipped by
            // ExtensionLoader itself - it must never stop the rest of the
            // extension directory from loading.
        }
    }
}

BOOL WINAPI DllMain(const HINSTANCE hInst, const DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);

        loadAllExtensions(extensionDirectory(hInst));

        ExtensionsManager::install();
    }
    return TRUE;
}

BaseExtension* ExtensionLoader::load(const std::wstring& dllPath) {
    const HMODULE module = LoadLibraryW(dllPath.c_str());
    if (!module) {
        LOG_ERROR_TO("ExtensionLoader", "Failed to load extension DLL (error {}): {}", GetLastError(), std::string(dllPath.begin(), dllPath.end()));
        return nullptr;
    }

    const auto create = reinterpret_cast<BaseExtension*(*)()>(GetProcAddress(module, CREATE_EXTENSION_SYMBOL));
    if (!create) {
        LOG_ERROR_TO("ExtensionLoader", "Extension DLL missing '{}' export: {}", CREATE_EXTENSION_SYMBOL, std::string(dllPath.begin(), dllPath.end()));
        FreeLibrary(module);
        return nullptr;
    }

    BaseExtension* extension = create();
    if (!extension) {
        LOG_ERROR_TO("ExtensionLoader", "createExtension() returned nullptr: {}", std::string(dllPath.begin(), dllPath.end()));
        FreeLibrary(module);
        return nullptr;
    }

    // Deliberately no FreeLibrary() on the success path: the extension's
    // vtable/code must stay resident in this module for the process
    // lifetime, exactly like the statically-linked extensions.
    return extension;
}