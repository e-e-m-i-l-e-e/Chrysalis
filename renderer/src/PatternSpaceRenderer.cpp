#include "PatternSpaceRenderer.h"

using namespace Chrysalis;

PatternSpaceRenderer::PatternSpaceRenderer(MainOpenGLProgram* program, PatternSpaceRendererData* rendererData)
    : BaseRenderer(rendererData), program_(program) {}

void PatternSpaceRenderer::draw() {
    program_->setColor(50.f / 255.f, 59.f / 255.f, 66.f / 255.f, 1.f);
    // for (const auto& [from, count]: spaceRendererData_->linesRanges()) {
    //     glDrawArrays(GL_LINE_STRIP, from, count);
    // }
    // for (const auto& [from, count]: spaceRendererData_->arrowsRanges()) {
    //     glDrawArrays(GL_TRIANGLE_STRIP, from, count);
    // }
    program_->setPointRadius(pointRadius_);
    glDrawArrays(GL_POINTS, 0, data_->count());
    program_->setPointRadius(0);
}

void PatternSpaceRenderer::scaleChanged(const float scale) {
    pointRadius_ = 0.25f * scale;
}

void PatternSpaceRenderer::pointAdded(const Point* point) {
    data_->addPoint(point);
}

void PatternSpaceRenderer::relativePointAdded(const Point* from, const Point* to) {
    data_->addPoint(to);
}
