#include "ChrysalisRenderer.h"

#include <iostream>
#include <QOpenGLFramebufferObject>

#include "Project.h"

#include "Logger.h"
#define LOGGER_NAME "Chrysalis Renderer"

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

ChrysalisRenderer::ChrysalisRenderer(ChrysalisOpenGLProgram* program,
                                     CursorRenderer* cursorRenderer,
                                     CartesianRenderer* cartesianRenderer)
    : program_(program), cursorRenderer_(cursorRenderer), cartesianRenderer_(cartesianRenderer) {}

ChrysalisRenderer::~ChrysalisRenderer() {
    delete program_;
    delete cartesianRenderer_;
}

void ChrysalisRenderer::initialize() {
    const auto parameters = new ProjectParameters();
    parameters->addParameter(new Parameter("Length", 66));
    parameters->addParameter(new Parameter("Bust", 96));
    parameters->addParameter(new Parameter("Bust Height", 36));
    parameters->addParameter(new Parameter("Back Width", 31));
    parameters->addParameter(new Parameter("Neck", 38));
    parameters->addParameter(new Parameter("Shoulder Length", 11));
    parameters->addParameter(new Parameter("Shoulder To Waist Back", 42));
    parameters->addParameter(new Parameter("Shoulder To Waist Front", 54));
    parameters->addParameter(new Parameter("Sleeve Length", 62));

    auto project = PB::Project(parameters);
    auto back = project.addPattern("Back");
    // auto pattern1 = project.addPattern("Back");
    // pattern1
    //     .addPoint("A", 0, 0)
    //     .nextPoint("B", Space::Direction::UP, 10)
    //     .addPoint("C", 10, 10)
    //     .nextPoint("D", Space::Direction::DOWN, 10);
    // PatternRenderer* patternRenderer1 = new PatternRenderer(
    //     new PatternSpaceRenderer(program_, pattern1.getSpaceRendererData()),
    //     new PatternShapeRenderer()
    // );
    // patternRenderers_.push_back(patternRenderer1);

    // auto pattern2 = project.addPattern("Front");
    // pattern2
    //     .addPoint("A", 7, 5)
    //     .nextPoint("B", Space::Direction::UP, 20)
    //     .nextPoint("C", Space::Direction::RIGHT, 5)
    //     .nextPoint("D", Space::Direction::DOWN, 7)
    //     .nextPoint("E", Space::Direction::RIGHT, 10)
    //     .nextPoint("F", Space::Direction::DOWN, 10)
    //     .addPoint("D", "G", Space::Direction::DOWN, 3);
    //
    // PatternRenderer* patternRenderer2 = new PatternRenderer(
    //     new PatternSpaceRenderer(program_, pattern2.getSpaceRendererData()),
    //     new PatternShapeRenderer()
    // );
    // patternRenderers_.push_back(patternRenderer2);

    program_->initialize();
    cartesianRenderer_->initialize();
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->initialize();
    }
    cursorRenderer_->initialize();
}

QOpenGLFramebufferObject* ChrysalisRenderer::createFramebufferObject(const QSize& size) {
    area_.setSize(size / scale_);
    cartesianRenderer_->changeArea(area_);
    cartesianRenderer_->upload();
    return Renderer::createFramebufferObject(size);
}

void ChrysalisRenderer::changeOffset(QPointF&& delta) {
    area_ -= delta * area_;
    cartesianRenderer_->changeArea(area_);
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
                cursorRenderer_->displayCursor({point.x(), point.y()});
                return;
            }
        }
    }
    cursorRenderer_->hideCursor();
}

void ChrysalisRenderer::render() {
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.ortho(
        0, framebufferObject()->width(),
        framebufferObject()->height(), 0,
        -1, 1
    );
    projection.scale(scale_);
    projection.translate(-area_.x(), -area_.y(), 0);

    program_->bind();
    program_->setProjection(projection);
    cartesianRenderer_->render();
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->render();
    }
    cursorRenderer_->render();
    program_->release();
}

void ChrysalisRenderer::synchronize(QQuickFramebufferObject* object) {
    bool shouldAnimate = false;
    shouldAnimate |= cursorRenderer_->animate();
    cartesianRenderer_->upload();
    if (shouldAnimate) object->update();
}
