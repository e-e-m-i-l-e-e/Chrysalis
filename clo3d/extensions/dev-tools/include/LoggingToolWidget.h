//
// Created by emily on 24/04/2026.
//

#ifndef FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H
#define FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H

#include <QWidget>

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class LoggingToolWidget;
    }

    QT_END_NAMESPACE

    class LoggingToolWidget : public QWidget {
        Q_OBJECT

    public:
        explicit LoggingToolWidget(QWidget *parent = nullptr);

        ~LoggingToolWidget() override;

    private:
        Ui::LoggingToolWidget *ui;
    };
} // UI

#endif //FASHIONDESIGNAPPS_LOGGINGTOOLWIDGET_H