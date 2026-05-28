#ifndef FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H
#define FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H

#include <QStackedWidget>

#include "BaseExtensionSettingsWidget.h"
#include "LoggerRegistryModel.h"
#include "LoggingToolSettings.h"
#include "LogLevelDelegate.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class LoggingToolSettingsWidget;
    }

    QT_END_NAMESPACE

    class LoggingToolSettingsWidget: public BaseExtensionSettingsWidget {
        Q_OBJECT
    public:
        explicit LoggingToolSettingsWidget(LoggingToolSettings* settings, LoggerRegistryModel* registryModel, LogLevelDelegate* logLevelDelegate, QStackedWidget* sinks, QWidget *parent = nullptr);
        ~LoggingToolSettingsWidget() override;

        void read() override;
        void write() override;

    private slots:
        void flush() const;
        void openInEditor() const;
        void resetSelection() const;
        void chooseLoggingDirectory();
    private:
        Ui::LoggingToolSettingsWidget *ui;

        QStackedWidget* sinks_;
        LoggingToolSettings* settings_;
        LoggerRegistryModel* registryModel_;
        LogLevelDelegate* logLevelDelegate_;
    };
} // UI

#endif //FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H