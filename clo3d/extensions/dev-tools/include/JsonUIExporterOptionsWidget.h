#ifndef FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONSWIDGET_H

#include <QWidget>

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class JsonUIExporterOptionsWidget;
    }

    QT_END_NAMESPACE

    class JsonUIExporterOptionsWidget : public QWidget {
        Q_OBJECT

    public:
        explicit JsonUIExporterOptionsWidget(QWidget *parent = nullptr);

        ~JsonUIExporterOptionsWidget() override;

    private:
        Ui::JsonUIExporterOptionsWidget *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONSWIDGET_H