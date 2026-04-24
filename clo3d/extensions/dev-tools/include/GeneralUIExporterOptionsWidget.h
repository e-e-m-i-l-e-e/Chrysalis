//
// Created by emily on 24/04/2026.
//

#ifndef FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONSWIDGET_H

#include <QWidget>

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class GeneralUIExporterOptionsWidget;
    }

    QT_END_NAMESPACE

    class GeneralUIExporterOptionsWidget : public QWidget {
        Q_OBJECT

    public:
        explicit GeneralUIExporterOptionsWidget(QWidget *parent = nullptr);

        ~GeneralUIExporterOptionsWidget() override;

    private:
        Ui::GeneralUIExporterOptionsWidget *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONSWIDGET_H