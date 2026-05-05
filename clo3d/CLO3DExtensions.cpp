#include <Windows.h>

#include "ExtensionsManager.h"

#include "PatternBuilder.h"
#include "AuthenticatorExtension.h"
#include "DevToolsExtension.h"
#include "JsonUIExporter.h"
#include "JsonUIExporterOptions.h"
#include "XmlUIExporter.h"
#include "XmlUIExporterOptions.h"

BOOL WINAPI DllMain(HINSTANCE hInst, const DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);
#ifdef EXTEND_WITH_AUTHENTICATOR
        ExtensionsManager::addExtension(new AuthenticatorExtension());
#endif
#ifdef EXTEND_WITH_PATTERN_BUILDER
        ExtensionsManager::addExtension(new PatternBuilder());
#endif
#ifdef EXTEND_WITH_DEV_TOOLS
        const auto devToolsExtension = new DevToolsExtension();
        const auto generalUIExporterOptions = new GeneralUIExporterOptions();
        const auto uiExporterTool = new UIExporterTool(generalUIExporterOptions);

        const auto jsonUIExporterOptions = new JsonUIExporterOptions();
        const auto jsonUIExporter = new JsonUIExporter(jsonUIExporterOptions);
        uiExporterTool->addExporter(jsonUIExporter);

        const auto xmlUIExporterOptions = new XmlUIExporterOptions();
        const auto xmlUIExporter = new XmlUIExporter(xmlUIExporterOptions);
        uiExporterTool->addExporter(xmlUIExporter);
        ExtensionsManager::addExtension(devToolsExtension);
#endif
        ExtensionsManager::install();
    }
    return TRUE;
}
