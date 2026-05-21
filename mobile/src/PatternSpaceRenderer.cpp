#include "PatternSpaceRenderer.h"

PatternSpaceRenderer::PatternSpaceRenderer(ChrysalisOpenGLProgram* program, const SpaceRendererData* spaceRendererData)
    : program_(program), spaceRendererData_(spaceRendererData) {}

void PatternSpaceRenderer::initialize() {
    data_ = spaceRendererData_->getVBO();
    BaseRenderer::initialize();
}

void PatternSpaceRenderer::render() {
    program_->setColor(1.f, 0.f, 0.f, 1.f);
    vao.bind();
    for (const auto& [from, count]: spaceRendererData_->linesRanges()) {
        glDrawArrays(GL_LINE_STRIP, from, count);
    }
    for (size_t i = spaceRendererData_->arrowsRange().from; i <= spaceRendererData_->arrowsRange().from + spaceRendererData_->arrowsRange().count; i += 4) {
        glDrawArrays(GL_TRIANGLE_STRIP, i, 4);
    }
    program_->setPointRadius(0.25 * scale_);
    glDrawArrays(GL_POINTS, spaceRendererData_->pointsRange().from, spaceRendererData_->pointsRange().count);
    program_->setPointRadius(0);
    vao.release();
}

void PatternSpaceRenderer::scaleChanged(const float scale) {
    scale_ = scale;
}