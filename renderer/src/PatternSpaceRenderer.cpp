#include "PatternSpaceRenderer.h"

using namespace Chrysalis;

PatternSpaceRenderer::PatternSpaceRenderer(MainOpenGLProgram* program, PatternSpaceRendererData* rendererData)
    : BaseRenderer(rendererData), program_(program) {}

void PatternSpaceRenderer::draw() {
    program_->setColor(50.f / 255.f, 59.f / 255.f, 66.f / 255.f, 1.f);
    glDrawArrays(GL_LINES, 0, data_->linesCount());
    // for (const auto& [from, count]: spaceRendererData_->arrowsRanges()) {
    //     glDrawArrays(GL_TRIANGLE_STRIP, from, count);
    // }
    program_->setPointRadius(pointRadius_);
    glDrawArrays(GL_POINTS, data_->linesCount(), data_->pointsCount());
    program_->setPointRadius(0);
}

void PatternSpaceRenderer::scaleChanged(const float scale) {
    pointRadius_ = 0.25f * scale;
}
