#ifndef FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H
#define FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H

#include "BaseExtensionSettingsWidget.h"
#include "LoggingToolSettings.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class LoggingToolSettingsWidget;
    }

    QT_END_NAMESPACE

    class LoggingToolSettingsWidget: public BaseExtensionSettingsWidget {
        Q_OBJECT
    public:
        explicit LoggingToolSettingsWidget(LoggingToolSettings* settings, QWidget *parent = nullptr);
        ~LoggingToolSettingsWidget() override;

    private:
        Ui::LoggingToolSettingsWidget *ui;
        LoggingToolSettings* settings_;
    };
} // UI

#endif //FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H