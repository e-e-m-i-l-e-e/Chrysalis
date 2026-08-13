#include "ProjectRenderer.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Chrysalis;

ProjectRenderer::ProjectRenderer(MainOpenGLProgram* program, CartesianRenderer* cartesianRenderer, CursorRenderer* cursorRenderer)
    : program_(program), cursorRenderer_(cursorRenderer), cartesianRenderer_(cartesianRenderer) {
}

ProjectRenderer::~ProjectRenderer() {
    delete program_;
    delete cursorRenderer_;
    delete cartesianRenderer_;
}

void ProjectRenderer::initialize() const {
    program_->initialize();
    cursorRenderer_->initialize();
    cartesianRenderer_->initialize();
}

void ProjectRenderer::useProject(const Project* project) {
    patternRenderers_.clear();
    for (const auto& pattern: *project->getPatterns()) {
        const auto patternTraceRendererData = new PatternTraceRendererData();
        pattern->getSpace()->trace::addObserver(patternTraceRendererData);
        const auto patternShapeRendererData = new PatternShapeRendererData();
        pattern->getSpace()->shape::addObserver(patternShapeRendererData);
        patternRenderers_.emplace_back(
            new PatternTraceRenderer(program_, patternTraceRendererData),
            new PatternShapeRenderer(program_, patternShapeRendererData)
        );
        patternRenderers_.back().initialize();
    }
}

void ProjectRenderer::areaSizeChanged(const float width, const float height) {
    area_.setSize(width / scale_, height / scale_);
    cartesianRenderer_->changeArea(area_);
    updateProjectionMatrix();
}

void ProjectRenderer::areaOffsetChanged(const float deltaX, const float deltaY) {
    area_.offset(deltaX, deltaY);
    cartesianRenderer_->changeArea(area_);
    updateProjectionMatrix();
}

void ProjectRenderer::scaleChanged(const float scaleFactor, const float zoomX, const float zoomY) {
    area_.scale(scaleFactor);
    area_.offset(zoomX * (1 - scaleFactor), zoomY * (1 - scaleFactor));
    scale_ *= scaleFactor;
    cartesianRenderer_->changeArea(area_);
    for (const auto& patternRenderer: patternRenderers_) patternRenderer.scaleChanged(scale_);
    updateProjectionMatrix();
}

void ProjectRenderer::cursorPositionChanged(const float x, const float y) const {
    const float cursorX = x * area_.width() + area_.x();
    const float cursorY = y * area_.height() + area_.y();
    for (const auto& patternRenderer: patternRenderers_) {
        if (const Point* point = patternRenderer.traceRenderer()->pointAtPosition(cursorX, cursorY)) {
            cursorRenderer_->displayCursor(point->x(), point->y());
            return;
        }
    }
    cursorRenderer_->hideCursor();
}

void ProjectRenderer::updateProjectionMatrix() {
    projection_ = glm::ortho(
        0.f, area_.width() * scale_,
        area_.height() * scale_, 0.f,
        -1.f, 1.f
    );
    projection_ = glm::scale(projection_, glm::vec3(scale_, scale_, 1.0f));
    projection_ = glm::translate(projection_, glm::vec3(-area_.x(), -area_.y(), 0.0f));
}

void ProjectRenderer::render() const {
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(11.0f / 255.0f, 9.0f / 255.0f, 10.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    program_->bind();
    program_->setProjection(projection_);
    cartesianRenderer_->render();
    for (const auto& patternRenderer: patternRenderers_) patternRenderer.render();
    cursorRenderer_->render();
}

bool ProjectRenderer::prepareNextFrame() const {
    cartesianRenderer_->upload();
    for (const auto& patternRenderer: patternRenderers_) patternRenderer.upload();
    return cursorRenderer_->animate();
}
