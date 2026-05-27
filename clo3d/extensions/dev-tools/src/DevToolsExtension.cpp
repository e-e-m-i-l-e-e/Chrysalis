#include "DevToolsExtension.h"

#include "UIExporterTool.h"
#include "UIExporterToolSettingsWidget.h"

DevToolsExtension::~DevToolsExtension() {
    for (const auto devTool: devTools_) {
        delete devTool;
    }
}

void DevToolsExtension::addDevTool(BaseDevTool* tool) {
    devTools_.push_back(tool);
}

void DevToolsExtension::startup() {
    for (const auto devTool: devTools_) {
        devTool->startup();
    }
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
