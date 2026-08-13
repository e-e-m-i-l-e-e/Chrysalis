#include "PatternTraceRenderer.h"

#include "Layout.h"

using namespace Chrysalis;

PatternTraceRenderer::PatternTraceRenderer(MainOpenGLProgram* program, PatternTraceRendererData* rendererData)
    : BaseRenderer(rendererData), program_(program) {}

void PatternTraceRenderer::draw() {
    program_->setColor(50.f / 255.f, 59.f / 255.f, 66.f / 255.f, 1.f);
    for (const auto& layout: data_->linesLayout()) {
        glDrawArrays(GL_LINES, layout.offset(), layout.count());
    }

    program_->setPointRadius(pointRadius_);
    const auto pointsLayout = data_->pointsLayout();
    glDrawArrays(GL_POINTS, pointsLayout.offset(), pointsLayout.count());
    program_->setPointRadius(0);

    program_->setColor(40.f / 255.f, 49.f / 255.f, 56.f / 255.f, 1.f);
    for (const auto& layout: data_->arrowsLayout()) {
        glDrawArrays(GL_TRIANGLE_STRIP, layout.offset(), layout.count());
    }
}

void PatternTraceRenderer::scaleChanged(const float scale) {
    pointRadius_ = PatternTraceRendererData::POINT_RADIUS * scale;
}

const Point* PatternTraceRenderer::pointAtPosition(const float x, const float y) const {
    return data_->pointAtPosition(x, y);
}
