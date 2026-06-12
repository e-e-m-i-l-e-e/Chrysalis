#include "ChrysalisRenderer.h"

#include "glad/gl.h"

#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>

#include "Project.h"

#include "Logging.h"
#define LOGGER_NAME "Chrysalis Renderer"

using namespace Chrysalis;

void ChrysalisRenderer::projectChanged(Project* project) {
    project_ = project;
    isProjectRendererInitialized_ = false;
}

void ChrysalisRenderer::initialize() {
    isInitialized_ = gladLoadGL([](const char* name) -> GLADapiproc {
        return QOpenGLContext::currentContext()->getProcAddress(name);
    });
    if (!isInitialized_) LOG_CRITICAL("Failed to load OpenGL functions.");
}

QOpenGLFramebufferObject* ChrysalisRenderer::createFramebufferObject(const QSize& size) {
    size_ = size;
    changeSize();
    return Renderer::createFramebufferObject(size);
}

void ChrysalisRenderer::changeSize() const {
    projectRenderer_->areaSizeChanged(static_cast<float>(size_.width()), static_cast<float>(size_.height()));
}

void ChrysalisRenderer::changeOffset(QPointF&& delta) const {
    projectRenderer_->areaOffsetChanged(static_cast<float>(delta.x()), static_cast<float>(delta.y()));
}

void ChrysalisRenderer::changeScale(const double scalar, QPointF&& center) const {
    projectRenderer_->scaleChanged(scalar, center.x(), center.y());
}

void ChrysalisRenderer::changeCursor(QPointF&& cursor) const {
    // cursor *= area_;
    // cursor += area_;
    // for (const auto& patternRenderer: patternRenderers_) {
    //     for (const auto& points = patternRenderer->getPoints();
    //          const auto& point: points) {
    //         constexpr double pointRadius = 0.25;
    //         if (const double distance = sqrt(pow(point.x() - cursor.x(), 2) + pow(point.y() - cursor.y(), 2));
    //             distance < pointRadius) {
    //             // cursorRenderer_->displayCursor(Vertex2f(point.x(), point.y()));
    //             return;
    //         }
    //     }
    // }
    // cursorRenderer_->hideCursor();
}

void ChrysalisRenderer::render() {
    projectRenderer_->render();
}

void ChrysalisRenderer::synchronize(QQuickFramebufferObject* object) {
    if (!isProjectRendererInitialized_) {
        delete projectRenderer_;
        const auto program = new MainOpenGLProgram();
        projectRenderer_ = new ProjectRenderer(project_, program, new CartesianRenderer(program));
        changeSize();
        projectRenderer_->initialize();
        isProjectRendererInitialized_ = true;
        project_->getInstructions()->execute();
    }

    while (!projectRenderer_->prepareNextFrame()) object->update();
    // bool shouldAnimate = false;
    // shouldAnimate |= cursorRenderer_->animate();
    // cartesianRenderer_->upload();
    // if (shouldAnimate) object->update();
}
