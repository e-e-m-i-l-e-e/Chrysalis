#include "PatternBuilderSceneElement.h"

#include "glad/gl.h"

#include <QQuickWindow>
#include <QOpenGLContext>

#include "ChrysalisRenderer.h"

#include "Logging.h"
#define LOGGER_NAME "Chrysalis Renderer"

PatternBuilderSceneElement::PatternBuilderSceneElement(QQuickItem* parent)
    : QQuickFramebufferObject(parent), renderer_([] {
        const auto program = new Chrysalis::MainOpenGLProgram();
        return new ChrysalisRenderer(program, new Chrysalis::CartesianRenderer(program, new CartesianRendererData()));
    }()) {
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

QQuickFramebufferObject::Renderer* PatternBuilderSceneElement::createRenderer() const {
    const static bool isInitialized = gladLoadGL([](const char* name) -> GLADapiproc {
        return QOpenGLContext::currentContext()->getProcAddress(name);
    });
    if (!isInitialized) LOG_CRITICAL("Failed to load OpenGL functions.");
    renderer_->initialize();
    return renderer_;
}

void PatternBuilderSceneElement::projectChanged(Chrysalis::Project* project) {
    renderer_->useProject(project);
    project->getInstructions()->execute();
    update();
}

QPointF PatternBuilderSceneElement::normalize(QPointF&& point) const {
    point.setX(point.x() / width());
    point.setY(1 - point.y() / height());
    return point;
}

void PatternBuilderSceneElement::wheelEvent(QWheelEvent* event) {
    const auto center = normalize(event->position());
    renderer_->scaleChanged(1.f + static_cast<float>(event->angleDelta().y()) / 1000.f,
                            static_cast<float>(center.x()), static_cast<float>(center.y()));
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
    const auto position = normalize(event->position());
    const auto delta = position - mousePosition_;
    renderer_->areaOffsetChanged(static_cast<float>(delta.x()), static_cast<float>(delta.y()));
    mousePosition_ = position;
    update();
}

void PatternBuilderSceneElement::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) isLeftMouseButtonPressed_ = false;
}