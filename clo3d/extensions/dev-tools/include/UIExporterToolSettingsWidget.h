#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H

#include "BaseExtensionsSettingsPageWidget.h"
#include "UIExporterToolSettings.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class UIExporterToolSettingsWidget;
    }

    QT_END_NAMESPACE

    class UIExporterToolSettingsWidget: public BaseExtensionsSettingsPageWidget {
        Q_OBJECT
    public:
        explicit UIExporterToolSettingsWidget(UIExporterToolSettings& tool, QWidget *parent = nullptr);
        ~UIExporterToolSettingsWidget() override;

        void save() override;
        void reset() override;
        void read() override;
    private:
        Ui::UIExporterToolSettingsWidget *ui;
        UIExporterToolSettings& settings;
    };
} // UI

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H