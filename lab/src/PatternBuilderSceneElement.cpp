#include "PatternBuilderSceneElement.h"

#include <QQuickWindow>

#include <iostream>

#include "ChrysalisRenderer.h"

PatternBuilderSceneElement::PatternBuilderSceneElement(QQuickItem* parent)
    : QQuickFramebufferObject(parent), renderer_(new ChrysalisRenderer()) {
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

QQuickFramebufferObject::Renderer* PatternBuilderSceneElement::createRenderer() const {
    renderer_->initialize();
    return renderer_;
}

void PatternBuilderSceneElement::projectChanged(Chrysalis::Project* project) {
    renderer_->projectChanged(project);
    update();
}

QPointF PatternBuilderSceneElement::normalize(QPointF&& point) const {
    point.setX(point.x() / width());
    point.setY(1 - point.y() / height());
    return point;
}

void PatternBuilderSceneElement::wheelEvent(QWheelEvent* event) {
    renderer_->changeScale(1.f + event->angleDelta().y() / 1000.f, normalize(event->position()));
    update();
}

void PatternBuilderSceneElement::hoverMoveEvent(QHoverEvent* event) {
    renderer_->changeCursor(normalize(event->position()));
    update();
}

void PatternBuilderSceneElement::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isLeftMouseButtonPressed_ = true;
        mousePosition_ = normalize(event->position());
    }
}

void PatternBuilderSceneElement::mouseMoveEvent(QMouseEvent* event) {
    if (!isLeftMouseButtonPressed_) return;
    renderer_->changeOffset(normalize(event->position()) - mousePosition_);
    mousePosition_ = normalize(event->position());
    update();
}

void PatternBuilderSceneElement::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) isLeftMouseButtonPressed_ = false;
}