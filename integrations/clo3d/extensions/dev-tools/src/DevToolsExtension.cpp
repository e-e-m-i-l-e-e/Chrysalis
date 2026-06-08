#include "DevToolsExtension.h"

#include "BaseCommandArgumentsWidget.h"
#include "ExportPatternCommand.h"
#include "ExportPatternCommandArgumentsWidget.h"
#include "LoggingTool.h"
#include "UIExporterTool.h"
#include "UIExporterToolSettingsWidget.h"

DevToolsExtension::~DevToolsExtension() {
    for (const auto devTool: devTools_) {
        delete devTool;
    }
}

DevToolsExtension* DevToolsExtension::create() {
    const auto devToolsExtension = new DevToolsExtension();
    devToolsExtension->addDevTool(UIExporterTool::create());
    devToolsExtension->addDevTool(LoggingTool::create());
    return devToolsExtension;
}

void DevToolsExtension::addDevTool(BaseDevTool* tool) {
    devTools_.push_back(tool);
}

void DevToolsExtension::startup() {
    for (const auto devTool: devTools_) {
        devTool->startup();
    }
}

void DevToolsExtension::configureCommands(CommandRunner* runner) {
    runner->add<ExportPatternCommand, ExportPatternCommandArguments, UI::ExportPatternCommandArgumentsWidget>();
}

void DevToolsExtension::configureSettings(ExtensionsSettings* extensionsSettings) {
    for (const auto devTool: devTools_) {
        devTool->configureSettings(extensionsSettings);
    }
}

void DevToolsExtension::configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) {
    for (const auto devTool: devTools_) {
        devTool->configureSettingsUI(extensionsSettingsDialog);
    }
}
