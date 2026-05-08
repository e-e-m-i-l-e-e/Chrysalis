#include "LoggingTool.h"

#include "LoggingToolSettingsWidget.h"

LoggingTool::LoggingTool(LoggingToolSettings *settings): settings_(settings) {}

LoggingTool::~LoggingTool() {
    delete settings_;
}

void LoggingTool::configureSettings(ExtensionsSettings* extensionsSettings) {
    extensionsSettings->addSettings(settings_);
}

void LoggingTool::configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) {
    extensionsSettingsDialog->addPage(new UI::LoggingToolSettingsWidget(settings_, extensionsSettingsDialog));
}
