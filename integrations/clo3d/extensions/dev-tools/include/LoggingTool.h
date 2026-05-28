#ifndef CHRYSALIS_LOGGINGTOOL_H
#define CHRYSALIS_LOGGINGTOOL_H

#include <spdlog/sinks/qt_sinks.h>

#include <QStackedWidget>

#include "BaseDevTool.h"
#include "LoggerTextEditSink.h"
#include "LoggingToolSettings.h"
#include "BaseLoggerRegistryListener.h"

class LoggingTool: public BaseDevTool, public BaseLoggerRegistryListener {
public:
    explicit LoggingTool(LoggerRegistry& registry, LoggingToolSettings* settings);
    ~LoggingTool() override;

    void loggerAdded(Logger* logger) override;

    void startup() override;
    void configureSettings(ExtensionsSettings *extensionsSettings) override;
    void configureSettingsUI(UI::ExtensionsSettingsDialog *extensionsSettingsDialog) override;
private:
    void addWidgetSink(Logger* logger) const;

    UI::LoggerTextEditSink* commonWidgetSink_ = nullptr;

    QStackedWidget* sinks_ = nullptr;
    LoggingToolSettings* settings_;
};

#endif //CHRYSALIS_LOGGINGTOOL_H