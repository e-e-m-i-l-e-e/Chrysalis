#include "ProjectSceneElement.h"

#include "glad/gl.h"

#include <QQuickWindow>
#include <QOpenGLContext>

#include "Logging.h"
#define LOGGER_NAME "Project Scene"

using namespace Chrysalis;

ProjectSceneElement::ProjectSceneElement(QQuickItem* parent)
    : QQuickFramebufferObject(parent), renderer_([] {
        const auto program = new MainOpenGLProgram();
        return new Renderer(program, new CartesianRenderer(program, new CartesianRendererData()), new CursorRenderer(program, new CursorRendererData()));
    }()) {
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

ProjectSceneElement::Renderer::Renderer(MainOpenGLProgram* program, CartesianRenderer* cartesianRenderer, CursorRenderer* cursorRenderer)
    : ProjectRenderer(program, cartesianRenderer, cursorRenderer) {}

ProjectSceneElement::Renderer* ProjectSceneElement::createRenderer() const {
    const static bool isInitialized = gladLoadGL([](const char* name) -> GLADapiproc {
        return QOpenGLContext::currentContext()->getProcAddress(name);
    });
    if (!isInitialized) LOG_CRITICAL("Failed to load OpenGL functions.");
    renderer_->initialize();
    return renderer_;
}

void ProjectSceneElement::projectChanged(const Project* project) {
    renderer_->changeProject(project);
    update();
}

void ProjectSceneElement::Renderer::changeProject(const Project* project) {
    pendingProject_ = project;
}

void ProjectSceneElement::Renderer::render() {
    ProjectRenderer::render();
}

void ProjectSceneElement::Renderer::synchronize(QQuickFramebufferObject* object) {
    if (pendingProject_) {
        useProject(pendingProject_.value());
        pendingProject_.value()->getInstructions()->execute();
        pendingProject_.reset();
    }
    if (prepareNextFrame()) object->update();
}

QOpenGLFramebufferObject* ProjectSceneElement::Renderer::createFramebufferObject(const QSize& size) {
    areaSizeChanged(static_cast<float>(size.width()), static_cast<float>(size.height()));
    return QQuickFramebufferObject::Renderer::createFramebufferObject(size);
}

QPointF ProjectSceneElement::normalize(QPointF&& point) const {
    point.setX(point.x() / width());
    point.setY(1 - point.y() / height());
    return point;
}

void ProjectSceneElement::wheelEvent(QWheelEvent* event) {
    const auto center = normalize(event->position());
    renderer_->scaleChanged(1.f + static_cast<float>(event->angleDelta().y()) / 1000.f,
                            static_cast<float>(center.x()), static_cast<float>(center.y()));
    update();
}

void ProjectSceneElement::hoverMoveEvent(QHoverEvent* event) {
    const auto position = normalize(event->position());
    renderer_->cursorPositionChanged(position.x(), position.y());
    update();
}

void ProjectSceneElement::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isLeftMouseButtonPressed_ = true;
        mousePosition_ = normalize(event->position());
    }
}

void ProjectSceneElement::mouseMoveEvent(QMouseEvent* event) {
    if (!isLeftMouseButtonPressed_) return;
    const auto position = normalize(event->position());
    const auto delta = position - mousePosition_;
    renderer_->areaOffsetChanged(static_cast<float>(delta.x()), static_cast<float>(delta.y()));
    mousePosition_ = position;
    update();
}

void ProjectSceneElement::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) isLeftMouseButtonPressed_ = false;
}