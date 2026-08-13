#include "PatternShapeRenderer.h"

using namespace Chrysalis;

PatternShapeRenderer::PatternShapeRenderer(MainOpenGLProgram* program, PatternShapeRendererData* data)
    : BaseRenderer(data), program_(program) {}

void PatternShapeRenderer::draw() {
    program_->setColor(50.f / 255.f, 59.f / 255.f, 66.f / 255.f, 0.25f);
    for (const auto& layout: data_->layout()) {
        glDrawArrays(GL_TRIANGLES, layout.offset(), layout.count());
    }
}