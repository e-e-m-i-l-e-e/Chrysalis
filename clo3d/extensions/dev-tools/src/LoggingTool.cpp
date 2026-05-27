#include "LoggingTool.h"

#include <iostream>
#include <ranges>
#include <spdlog/sinks/qt_sinks.h>

#include "ExtensionsSettings.h"
#include "Logging.h"
#include "LoggingToolSettingsWidget.h"

LoggingTool::LoggingTool(LoggerRegistry& registry, LoggingToolSettings* settings)
    : BaseLoggerRegistryListener(registry), settings_(settings) {}

LoggingTool::~LoggingTool() {
    delete sinks_;
    delete settings_;
}

void LoggingTool::addWidgetSink(Logger* logger) const {
    const auto sink = new QTextEdit(sinks_);
    sink->setReadOnly(true);

    logger->addSink(std::make_shared<spdlog::sinks::qt_color_sink_st>(sink, 100));
    logger->addSink(commonWidgetSink_);

    sinks_->addWidget(sink);
}

void LoggingTool::loggerAdded(Logger* logger) {
    if (!sinks_) return;
    addWidgetSink(logger);
}

void LoggingTool::startup() {
    const auto commonWidget = new QTextEdit(sinks_);
    commonWidget->setReadOnly(true);

    sinks_ = new QStackedWidget();
    sinks_->addWidget(commonWidget);
    commonWidgetSink_ = std::make_shared<spdlog::sinks::qt_color_sink_st>(commonWidget, 100);

    for (const auto& logger : registry_.getLoggers() | std::views::values) {
        addWidgetSink(logger);
    }
}

void LoggingTool::configureSettings(ExtensionsSettings* extensionsSettings) {
    extensionsSettings->addSettings(settings_);
}

void LoggingTool::configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) {
    const auto loggerRegistryModel = new LoggerRegistryModel(extensionsSettingsDialog, Logging::REGISTRY);
    const auto settingsWidget = new UI::LoggingToolSettingsWidget(settings_, loggerRegistryModel, sinks_, extensionsSettingsDialog);
    extensionsSettingsDialog->addPage(settingsWidget);
}
