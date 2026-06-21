#include "PatternSpaceRenderer.h"

using namespace Chrysalis;

PatternSpaceRenderer::PatternSpaceRenderer(MainOpenGLProgram* program, PatternSpaceRendererData* rendererData)
    : BaseRenderer(rendererData), program_(program) {}

void PatternSpaceRenderer::draw() {
    program_->setColor(50.f / 255.f, 59.f / 255.f, 66.f / 255.f, 1.f);
    glDrawArrays(GL_LINES, 0, data_->linesSize());
    program_->setPointRadius(pointRadius_);
    glDrawArrays(GL_POINTS, data_->linesSize() + data_->arrowsSize(), data_->pointsSize());
    program_->setPointRadius(0);
    program_->setColor(60.f / 255.f, 70.f / 255.f, 76.f / 255.f, 0.75f);
    for (int i = 0; i < data_->arrowsSize() / 4; i++) {
        glDrawArrays(GL_TRIANGLE_STRIP, data_->linesSize() + i * 4, 4);
    }
}

void PatternSpaceRenderer::scaleChanged(const float scale) {
    pointRadius_ = PatternSpaceRendererData::POINT_RADIUS * scale;
}

bool PatternSpaceRenderer::isPointed(const float x, const float y) const {
    return data_->isPointed(x, y);
}
