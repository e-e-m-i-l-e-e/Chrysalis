#include <Windows.h>

#include "ExtensionsManager.h"

#include "PatternBuilder.h"
#include "AuthenticatorExtension.h"
#include "DevToolsExtension.h"
#include "JsonUIExporter.h"
#include "JsonUIExporterOptions.h"
#include "Logging.h"
#include "LoggingTool.h"
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

        const auto uiExporterToolSettings = new UIExporterToolSettings();
        const auto generalUIExporterOptions = new GeneralUIExporterOptions();
        const auto uiExporterTool = new UIExporterTool(uiExporterToolSettings, generalUIExporterOptions);

        const auto jsonUIExporterOptions = new JsonUIExporterOptions();
        const auto jsonUIExporter = new JsonUIExporter(jsonUIExporterOptions);
        uiExporterTool->addExporter(jsonUIExporter);

        const auto xmlUIExporterOptions = new XmlUIExporterOptions();
        const auto xmlUIExporter = new XmlUIExporter(xmlUIExporterOptions);
        uiExporterTool->addExporter(xmlUIExporter);

        devToolsExtension->addDevTool(uiExporterTool);

        const auto loggingToolSettings = new LoggingToolSettings(Logging::REGISTRY);
        const auto loggingTool = new LoggingTool(Logging::REGISTRY, loggingToolSettings);
        devToolsExtension->addDevTool(loggingTool);

        ExtensionsManager::addExtension(devToolsExtension);
#endif
        ExtensionsManager::install();
    }
    return TRUE;
}
