#include "ClickableWidget.h"

using namespace UI;

ClickableWidget::ClickableWidget(QWidget *parent): QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground, true);
}

void ClickableWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    emit clicked();
}
