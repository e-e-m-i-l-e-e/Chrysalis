#ifndef CLOEXTENSIONS_CLICKABLEWIDGET_H
#define CLOEXTENSIONS_CLICKABLEWIDGET_H

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

#endif //CLOEXTENSIONS_CLICKABLEWIDGET_H