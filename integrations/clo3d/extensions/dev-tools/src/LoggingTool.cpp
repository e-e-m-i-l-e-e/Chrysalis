#include "LoggingTool.h"

#include <ranges>

#include "Logging.h"
#include "LoggerFormatter.h"
#include "ExtensionsSettings.h"
#include "LoggerTextEditSink.h"
#include "LoggingToolSettingsWidget.h"

LoggingTool::LoggingTool(LoggerRegistry& registry, LoggingToolSettings* settings)
    : BaseLoggerRegistryListener(registry), settings_(settings) {}

LoggingTool::~LoggingTool() {
    delete sinks_;
    delete settings_;
}

void LoggingTool::addWidgetSink(Logger* logger) const {
    const auto sinkWidget = new UI::LoggerTextEditSink(sinks_);
    sinkWidget->attach(logger);
    commonWidgetSink_->attach(logger);
    sinks_->addWidget(sinkWidget);
}

void LoggingTool::loggerAdded(Logger* logger) {
    settings_->read(registry_.size() - 1, logger);
    if (!sinks_) return;
    addWidgetSink(logger);
}

void LoggingTool::startup() {
    sinks_ = new QStackedWidget();
    commonWidgetSink_ = new UI::LoggerTextEditSink(sinks_);
    sinks_->addWidget(commonWidgetSink_);
    for (const auto& logger: registry_) {
        addWidgetSink(logger);
    }
}

void LoggingTool::configureSettings(ExtensionsSettings* extensionsSettings) {
    extensionsSettings->addSettings(settings_);
}

void LoggingTool::configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) {
    const auto loggerRegistryModel = new UI::LoggerRegistryModel(extensionsSettingsDialog, registry_);
    const auto logLevelDelegate = new UI::LogLevelDelegate(loggerRegistryModel);
    const auto settingsWidget = new UI::LoggingToolSettingsWidget(settings_, loggerRegistryModel, logLevelDelegate, sinks_, extensionsSettingsDialog);
    extensionsSettingsDialog->addPage(settingsWidget);
}
