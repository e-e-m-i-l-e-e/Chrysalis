#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H

#include "NamedWidget.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class UIExporterToolWidget;
    }

    QT_END_NAMESPACE

    class UIExporterToolWidget : public NamedWidget {
        Q_OBJECT
    public:
        explicit UIExporterToolWidget(QWidget *parent = nullptr);
        ~UIExporterToolWidget() override;
    private:
        Ui::UIExporterToolWidget *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H