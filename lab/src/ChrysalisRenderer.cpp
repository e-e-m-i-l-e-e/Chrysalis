#include "ChrysalisRenderer.h"

#include <QOpenGLFramebufferObject>
#include <glm/gtc/matrix_transform.hpp>

#include "Project.h"

#include "Logging.h"
#define LOGGER_NAME "Chrysalis Renderer"

#include "glad/gl.h"
#include <QOpenGLContext> // Needed to resolve the function loader

using namespace Chrysalis;

// --- Operators "*" and "/" use width and height of QRectF (scaling operations) ---------------------------------------

QPointF& operator*=(QPointF& point, const QRectF& rect) {
    point.setX(point.x() * rect.width());
    point.setY(point.y() * rect.height());
    return point;
}

QPointF operator*(QPointF point, const QRectF& rect) {
    return point *= rect;
}

QRectF& operator/=(QRectF& rect, const double denominator) {
    rect.setSize(rect.size() / denominator);
    return rect;
}

// --- Operators "+" and "-" use x and y of QRectF (translating operations) --------------------------------------------

QPointF& operator+=(QPointF& point, const QRectF& rect) {
    point.setX(point.x() + rect.x());
    point.setY(point.y() + rect.y());
    return point;
}

QRectF& operator-=(QRectF& rect, const QPointF& point) {
    rect.moveLeft(rect.x() - point.x());
    rect.moveTop(rect.y() - point.y());
    return rect;
}

QPointF operator+(QPointF point, const QRectF& rect) {
    return point += rect;
}

// ---------------------------------------------------------------------------------------------------------------------

ChrysalisRenderer::ChrysalisRenderer(MainOpenGLProgram* program,
                                     CartesianRenderer* cartesianRenderer)
    : program_(program), cartesianRenderer_(cartesianRenderer) {}

ChrysalisRenderer::~ChrysalisRenderer() {
    delete program_;
    delete cartesianRenderer_;
}

void ChrysalisRenderer::projectChanged(Chrysalis::Project* project) {
}

void ChrysalisRenderer::initialize() const {
    auto openGLContext = QOpenGLContext::currentContext();
    if (!openGLContext) {
        LOG_CRITICAL("GLAD: No active QOpenGLContext found in this thread!");
        return;
    }

    bool gladLoaded = gladLoadGL([](const char* name) -> GLADapiproc {
        return reinterpret_cast<GLADapiproc>(
            QOpenGLContext::currentContext()->getProcAddress(name)
        );
    });

    if (!gladLoaded) {
        LOG_CRITICAL("GLAD: Failed to initialize OpenGL context loaders!");
        return;
    }
    program_->initialize();
    cartesianRenderer_->initialize();
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->initialize();
    }
}

QOpenGLFramebufferObject* ChrysalisRenderer::createFramebufferObject(const QSize& size) {
    area_.setSize(size / scale_);
    cartesianRenderer_->changeArea(Area(area_.x(), area_.y(), area_.width(), area_.height()));
    cartesianRenderer_->upload();
    return Renderer::createFramebufferObject(size);
}

void ChrysalisRenderer::changeOffset(QPointF&& delta) {
    area_ -= delta * area_;
    cartesianRenderer_->changeArea(Area(area_.x(), area_.y(), area_.width(), area_.height()));
}

void ChrysalisRenderer::changeScale(const double scalar, QPointF&& center) {
    if (!framebufferObject()) return;
    area_ /= scalar;

    center *= 1 - scalar;
    changeOffset(std::move(center));

    scale_ *= scalar;
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->scaleChanged(scale_);
    }
}

void ChrysalisRenderer::changeCursor(QPointF&& cursor) const {
    cursor *= area_;
    cursor += area_;
    for (const auto& patternRenderer: patternRenderers_) {
        for (const auto& points = patternRenderer->getPoints();
             const auto& point: points) {
            constexpr double pointRadius = 0.25;
            if (const double distance = sqrt(pow(point.x() - cursor.x(), 2) + pow(point.y() - cursor.y(), 2));
                distance < pointRadius) {
                // cursorRenderer_->displayCursor(Vertex2f(point.x(), point.y()));
                return;
            }
        }
    }
    // cursorRenderer_->hideCursor();
}

void ChrysalisRenderer::render() {
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(11.0f / 255.0f, 9.0f / 255.0f, 10.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4x4 projection = glm::ortho(
        0.f, static_cast<float>(framebufferObject()->width()),
        static_cast<float>(framebufferObject()->height()), 0.f,
        -1.f, 1.f
    );
    projection = glm::scale(projection, glm::vec3(scale_, scale_, 1.0f));
    projection = glm::translate(projection, glm::vec3(-area_.x(), -area_.y(), 0.0f));

    program_->bind();
    program_->setProjection(projection);
    cartesianRenderer_->render();
    program_->release();
}

void ChrysalisRenderer::synchronize(QQuickFramebufferObject* object) {
    bool shouldAnimate = false;
    // shouldAnimate |= cursorRenderer_->animate();
    cartesianRenderer_->upload();
    if (shouldAnimate) object->update();
}
