#ifndef CHRYSALIS_UIEXPORTERTOOLWIDGET_H
#define CHRYSALIS_UIEXPORTERTOOLWIDGET_H

#include <functional>

#include "UIExporterToolSettings.h"
#include "BaseUIExporterOptionsWidget.h"
#include "BaseExtensionSettingsWidget.h"

namespace CLO3D::UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class UIExporterToolSettingsWidget;
    }
    QT_END_NAMESPACE

    class UIExporterToolSettingsWidget: public BaseExtensionSettingsWidget {
        Q_OBJECT
    public:
        explicit UIExporterToolSettingsWidget(UIExporterToolSettings* tool, QWidget *parent = nullptr);
        ~UIExporterToolSettingsWidget() override;

        void read() override;
        void write() override;
    private:
        void processOptions(void(BaseUIExporterOptionsWidget::*processor)()) const;

        Ui::UIExporterToolSettingsWidget *ui;
        UIExporterToolSettings* settings_;
    };
} // UI

#endif //CHRYSALIS_UIEXPORTERTOOLWIDGET_H