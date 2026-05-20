#include "PatternBuilderSceneElement.h"

#include <QQuickWindow>

#include <iostream>

#include "ChrysalisRenderer.h"
#include "PatternBuilderRenderer.h"

PatternBuilderSceneElement::PatternBuilderSceneElement(QQuickItem* parent)
    : QQuickFramebufferObject(parent), renderer_(new ChrysalisRenderer()) {
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

QQuickFramebufferObject::Renderer* PatternBuilderSceneElement::createRenderer() const {
    renderer_->initialize();
    return renderer_;
}

QPointF& PatternBuilderSceneElement::getMousePosition() {
    return mousePosition_;
}

void PatternBuilderSceneElement::wheelEvent(QWheelEvent* event) {
    QPointF position = event->position() * window()->devicePixelRatio();
    renderer_->changeScale(1.f + event->angleDelta().y() / 1000.f, position);
    update();
}

void PatternBuilderSceneElement::hoverMoveEvent(QHoverEvent* event) {
    mousePosition_ = event->position();
    update();
}

void PatternBuilderSceneElement::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isLeftMouseButtonPressed_ = true;
        mousePosition_ = event->position();
    }
}

void PatternBuilderSceneElement::mouseMoveEvent(QMouseEvent* event) {
    if (!isLeftMouseButtonPressed_) return;
    renderer_->changeOffset((event->position() - mousePosition_) * window()->devicePixelRatio());
    mousePosition_ = event->position();
    update();
}

void PatternBuilderSceneElement::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) isLeftMouseButtonPressed_ = false;
}