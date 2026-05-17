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

    renderer_->changeOffset(delta.x(), delta.y());
    update();
}

void PatternBuilderSceneElement::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) isMousePressed_ = false;
}

void PatternBuilderSceneElement::wheelEvent(QWheelEvent* event) {
    renderer_->changeScale(1.f + event->angleDelta().y() / 1000.f, event->position());
    update();
}

void PatternBuilderSceneElement::geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) {
    renderer_->changeGeometry({
        windowPosition_.x(), windowPosition_.y(),
        newGeometry.width(), newGeometry.height()
    });
    update();
}

void PatternBuilderSceneElement::itemChange(const ItemChange change, const ItemChangeData& data) {
    if (change == ItemSceneChange && data.window) {
        windowPosition_.setX(data.window->x());
        windowPosition_.setY(data.window->y());
        connect(data.window, &QWindow::xChanged, this, [this] {
            windowPosition_.setX(window()->x());
        });
        connect(data.window, &QWindow::yChanged, this, [this] {
            windowPosition_.setY(window()->y());
        });
    }
    return QQuickFramebufferObject::itemChange(change, data);
}
