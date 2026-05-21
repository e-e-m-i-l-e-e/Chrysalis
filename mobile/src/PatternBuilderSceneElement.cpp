#include "PatternBuilderSceneElement.h"

#include <QQuickWindow>

#include <iostream>

#include "ChrysalisRenderer.h"

PatternBuilderSceneElement::PatternBuilderSceneElement(QQuickItem* parent)
    : QQuickFramebufferObject(parent), renderer_([] {
        const auto program = new ChrysalisOpenGLProgram();
        const auto cursor = new CursorRenderer();
        const auto cartesian = new CartesianRenderer(program);
        return new ChrysalisRenderer(program, cursor, cartesian);
    }()) {
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
    QPointF position = event->position();
    position.setX(position.x() / window()->width());
    position.setY(position.y() / window()->height());
    renderer_->changeCursor(position);
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