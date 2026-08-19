#ifndef CHRYSALIS_LOGGINGTOOL_H
#define CHRYSALIS_LOGGINGTOOL_H

#include <spdlog/sinks/qt_sinks.h>

#include <QStackedWidget>

#include "BaseDevTool.h"
#include "LoggerTextEditSink.h"
#include "LoggingToolSettings.h"
#include "BaseLoggerRegistryListener.h"

namespace CLO3D {
    class LoggingTool: public BaseDevTool, public Logging::BaseLoggerRegistryListener {
    public:
        explicit LoggingTool(Logging::LoggerRegistry& registry, LoggingToolSettings* settings);
        ~LoggingTool() override;

        static LoggingTool* create();

        void loggerAdded(Logging::Logger* logger) override;

        void startup() override;
        void configureSettings(ExtensionsSettings* extensionsSettings) override;
        void configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) override;
    private:
        void addWidgetSink(Logging::Logger* logger) const;

        UI::LoggerTextEditSink* commonWidgetSink_ = nullptr;

        QStackedWidget* sinks_ = nullptr;
        LoggingToolSettings* settings_;
    };
}

#endif //CHRYSALIS_LOGGINGTOOL_H