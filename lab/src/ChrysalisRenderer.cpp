#include "ChrysalisRenderer.h"

#include "glad/gl.h"

#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>

#include "Project.h"

#include "Logging.h"
#define LOGGER_NAME "Chrysalis Renderer"

using namespace Chrysalis;

ChrysalisRenderer::ChrysalisRenderer(MainOpenGLProgram* program, CartesianRenderer* cartesianRenderer)
    : ProjectRenderer(program, cartesianRenderer) {}

QOpenGLFramebufferObject* ChrysalisRenderer::createFramebufferObject(const QSize& size) {
    areaSizeChanged(static_cast<float>(size.width()), static_cast<float>(size.height()));
    return Renderer::createFramebufferObject(size);
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
    ProjectRenderer::render();
}

void ChrysalisRenderer::synchronize(QQuickFramebufferObject* object) {
    while (!prepareNextFrame()) object->update();
    // bool shouldAnimate = false;
    // shouldAnimate |= cursorRenderer_->animate();
    // cartesianRenderer_->upload();
    // if (shouldAnimate) object->update();
}
