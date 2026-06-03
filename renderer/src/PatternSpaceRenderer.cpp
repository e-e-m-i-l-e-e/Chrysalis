#include "PatternSpaceRenderer.h"

using namespace Chrysalis;

PatternSpaceRenderer::PatternSpaceRenderer(MainOpenGLProgram* program, const RendererData* spaceRendererData)
    : program_(program), spaceRendererData_(spaceRendererData) {}

void PatternSpaceRenderer::initialize() {
    data_ = spaceRendererData_->getVBO();
    BaseRenderer::initialize();
}

void PatternSpaceRenderer::draw() {
    program_->setColor(50.f / 255.f, 59.f / 255.f, 66.f / 255.f, 1.f);
    for (const auto& [from, count]: spaceRendererData_->linesRanges()) {
        glDrawArrays(GL_LINE_STRIP, from, count);
    }
    for (const auto& [from, count]: spaceRendererData_->arrowsRanges()) {
        glDrawArrays(GL_TRIANGLE_STRIP, from, count);
    }
    program_->setPointRadius(0.25 * scale_);
    glDrawArrays(GL_POINTS, spaceRendererData_->pointsRange().first, spaceRendererData_->pointsRange().second);
    program_->setPointRadius(0);
}

void PatternSpaceRenderer::scaleChanged(const float scale) {
    scale_ = scale;
}

std::vector<Vertex3f> PatternSpaceRenderer::getPoints() const {
    return spaceRendererData_->getPoints();
}