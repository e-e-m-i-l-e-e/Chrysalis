#include "ClickableWidget.h"

using namespace UI;

ClickableWidget::ClickableWidget(QWidget *parent): QWidget(parent) {}

void ClickableWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    emit clicked();
}
