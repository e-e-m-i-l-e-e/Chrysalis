//
// Created by emily on 24/04/2026.
//

#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H

#include <QWidget>

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class UIExporterToolWidget;
    }

    QT_END_NAMESPACE

    class UIExporterToolWidget : public QWidget {
        Q_OBJECT

    public:
        explicit UIExporterToolWidget(QWidget *parent = nullptr);

        ~UIExporterToolWidget() override;

    private:
        Ui::UIExporterToolWidget *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOLWIDGET_H