#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H

#include <functional>

#include "UIExporterToolSettings.h"
#include "BaseUIExporterOptionsWidget.h"
#include "BaseExtensionSettingsWidget.h"

namespace UI {
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

        void save() override;
        void reset() override;
        void read() override;
    private:
        void processOptions(void(BaseUIExporterOptionsWidget::*processor)()) const;

        Ui::UIExporterToolSettingsWidget *ui;
        UIExporterToolSettings* settings_;
    };
} // UI

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H