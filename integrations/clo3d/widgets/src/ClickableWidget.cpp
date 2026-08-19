#include "ClickableWidget.h"

using namespace CLO3D::UI;

ClickableWidget::ClickableWidget(QWidget *parent): QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground, true);
}

void ClickableWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    emit clicked();
}
