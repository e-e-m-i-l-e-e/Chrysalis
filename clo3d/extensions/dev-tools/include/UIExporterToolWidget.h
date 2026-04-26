#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H

#include "BaseExtensionsSettingsPageWidget.h"
#include "UIExporterTool.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class UIExporterToolWidget;
    }

    QT_END_NAMESPACE

    class UIExporterToolWidget: public BaseExtensionsSettingsPageWidget {
        Q_OBJECT
    public:
        explicit UIExporterToolWidget(UIExporterTool& tool, QWidget *parent = nullptr);
        ~UIExporterToolWidget() override;

        void save() override;
        void reset() override;
    private:
        Ui::UIExporterToolWidget *ui;
        UIExporterTool& tool;
    };
} // UI

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H