#ifndef CHRYSALIS_CLICKABLEWIDGET_H
#define CHRYSALIS_CLICKABLEWIDGET_H

#include <QWidget>

namespace UI {
    class ClickableWidget: public QWidget {

        Q_OBJECT

    signals:
        void clicked();
    public:
        explicit ClickableWidget(QWidget *parent = nullptr);
    protected:
        void mousePressEvent(QMouseEvent *event) override;
    };
} // UI

#endif //CHRYSALIS_CLICKABLEWIDGET_H