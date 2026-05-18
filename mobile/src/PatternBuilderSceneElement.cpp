#include "PatternBuilderSceneElement.h"

#include <QQuickWindow>

#include <iostream>

#include "PatternBuilderRenderer.h"

PatternBuilderSceneElement::PatternBuilderSceneElement(QQuickItem* parent)
    : QQuickFramebufferObject(parent), renderer_(new PatternBuilderRenderer()) {
    setAcceptedMouseButtons(Qt::AllButtons);
}

QQuickFramebufferObject::Renderer* PatternBuilderSceneElement::createRenderer() const {
    renderer_->initialize();
    return renderer_;
}

void PatternBuilderSceneElement::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isMousePressed_ = true;
        mousePosition_ = event->position();
    }
}

void PatternBuilderSceneElement::mouseMoveEvent(QMouseEvent* event) {
    if (!isMousePressed_) return;

    const QPointF delta = event->position() - mousePosition_;
    mousePosition_ = event->position();

    renderer_->changeOffset(delta.x() * window()->devicePixelRatio(), delta.y() * window()->devicePixelRatio());
    update();
}

void PatternBuilderSceneElement::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) isMousePressed_ = false;
}

void PatternBuilderSceneElement::wheelEvent(QWheelEvent* event) {
    const QPointF position = event->position() * window()->devicePixelRatio();
    renderer_->changeScale(1.f + event->angleDelta().y() / 1000.f, position);
    update();
}
