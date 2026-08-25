
#include <filesystem>

#include "BaseExtension.h"
#include "ExtensionsManager.h"

#include "Logging.h"
#define LOGGER_NAME "CLO3DExtensions"

BOOL WINAPI DllMain(const HINSTANCE hInst, const DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);

        // --- Load Extensions -----------------------------------------------------------------------------------------

        std::error_code error;
        const auto iterator = std::filesystem::directory_iterator(CLO_EXTENSION_HOME, error);
        if (error) {
            LOG_CRITICAL(
                "Failed to walk through extensions directory: \"{}\". ERROR: {}.",
                CLO_EXTENSION_HOME, error.message()
            );
        }
        for (const auto& entry: iterator) {
            if (!entry.is_regular_file(error) || error) continue;

            auto fileExtension = entry.path().extension().wstring();
            std::ranges::transform(fileExtension, fileExtension.begin(), ::towlower);
            if (fileExtension != L".dll") continue;

            auto extensionFile = entry.path().wstring();
            const HMODULE module = LoadLibraryW(extensionFile.c_str());
            if (!module) {
                LOG_ERROR(
                    "Failed to load extension \"{}\". Error: {}.",
                    std::string(extensionFile.begin(), extensionFile.end()), GetLastError()
                );
                continue;
            }
            constexpr auto CREATE_EXTENSION_FUNCTION = "create";
            using CreateExtension = CLO3D::BaseExtension*(*)();
            const auto create = reinterpret_cast<CreateExtension>(GetProcAddress(module, CREATE_EXTENSION_FUNCTION));
            if (!create) {
                LOG_ERROR(
                    "Cannot find \"{}\" function in extension: {}",
                    CREATE_EXTENSION_FUNCTION, std::string(extensionFile.begin(), extensionFile.end())
                );
                FreeLibrary(module);
                continue;
            }
            CLO3D::ExtensionsManager::addExtension(std::unique_ptr<CLO3D::BaseExtension>(create()));
        }
        CLO3D::ExtensionsManager::install();
    }
    return TRUE;
}