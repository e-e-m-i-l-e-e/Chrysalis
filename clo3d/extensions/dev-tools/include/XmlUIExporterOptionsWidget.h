//
// Created by emily on 24/04/2026.
//

#ifndef FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONSWIDGET_H

#include <QWidget>

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class XmlUIExporterOptionsWidget;
    }

    QT_END_NAMESPACE

    class XmlUIExporterOptionsWidget : public QWidget {
        Q_OBJECT

    public:
        explicit XmlUIExporterOptionsWidget(QWidget *parent = nullptr);

        ~XmlUIExporterOptionsWidget() override;

    private:
        Ui::XmlUIExporterOptionsWidget *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONSWIDGET_H