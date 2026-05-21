#include "ChrysalisRenderer.h"

#include <iostream>
#include <QOpenGLFramebufferObject>

#include "Project.h"

#include "Logger.h"
#define LOGGER_NAME "Chrysalis Renderer"

ChrysalisRenderer::ChrysalisRenderer(ChrysalisOpenGLProgram* program,
                                     CursorRenderer* cursorRenderer,
                                     CartesianRenderer* cartesianRenderer)
    : program_(program), cursorRenderer_(cursorRenderer), cartesianRenderer_(cartesianRenderer) {}

ChrysalisRenderer::~ChrysalisRenderer() {
    delete program_;
    delete cartesianRenderer_;
}

void ChrysalisRenderer::initialize() {
    auto project = PB::Project();

    auto pattern1 = project.addPattern("Pattern 1");
    pattern1
        .addPoint("A", 0, 0)
        .nextPoint("B", Space::Direction::UP, 10)
        .addPoint("C", 10, 10)
        .nextPoint("D", Space::Direction::DOWN, 10);
    PatternRenderer* patternRenderer1 = new PatternRenderer(
        new PatternSpaceRenderer(program_, pattern1.getSpaceRendererData()),
        new PatternShapeRenderer()
    );
    patternRenderers_.push_back(patternRenderer1);

    auto pattern2 = project.addPattern("Pattern 2");
    pattern2
        .addPoint("A", 7, 5)
        .nextPoint("B", Space::Direction::UP, 20)
        .nextPoint("C", Space::Direction::RIGHT, 5)
        .nextPoint("D", Space::Direction::DOWN, 7)
        .nextPoint("E", Space::Direction::RIGHT, 10)
        .nextPoint("F", Space::Direction::DOWN, 10);
    PatternRenderer* patternRenderer2 = new PatternRenderer(
        new PatternSpaceRenderer(program_, pattern2.getSpaceRendererData()),
        new PatternShapeRenderer()
    );
    patternRenderers_.push_back(patternRenderer2);

    program_->initialize();
    cartesianRenderer_->initialize();
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->initialize();
    }
}

QOpenGLFramebufferObject* ChrysalisRenderer::createFramebufferObject(const QSize& size) {
    area_.setSize(size / scale_);
    cartesianRenderer_->changeArea(area_);
    cartesianRenderer_->upload();
    return Renderer::createFramebufferObject(size);
}

void ChrysalisRenderer::changeOffset(const QPointF& delta) {
    area_.moveLeft(area_.x() - delta.x() / scale_);
    area_.moveTop(area_.y() + delta.y() / scale_);
    cartesianRenderer_->changeArea(area_);
}

void ChrysalisRenderer::changeScale(const double scalar, QPointF& center) {
    if (!framebufferObject()) return;
    center.setY(center.y() - area_.height() * scale_);
    const QPointF centerBefore = center / scale_;
    scale_ *= scalar;
    area_.setSize({framebufferObject()->width() / scale_, framebufferObject()->height() / scale_});
    changeOffset(center - centerBefore * scale_);
    for (const auto patternRenderer: patternRenderers_) {
        patternRenderer->scaleChanged(scale_);
    }
}

void ChrysalisRenderer::changeCursor(const QPointF& position) {
    QPointF p = position;
    std::cout << "Change cursor position: " << p.x() * area_.width() + area_.x() << " " << (1 - p.y()) * area_.height() + area_.y() << std::endl;
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
    program_->release();
}

void ChrysalisRenderer::synchronize(QQuickFramebufferObject* object) {
    cartesianRenderer_->upload();
}
