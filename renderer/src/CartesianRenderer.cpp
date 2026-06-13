#include "CartesianRenderer.h"

#include <iostream>

using namespace Chrysalis;

CartesianRenderer::CartesianRenderer(MainOpenGLProgram* program, CartesianRendererData* data)
    : BaseRenderer(data), program_(program) {}

void CartesianRenderer::draw() {
    program_->setColor(22.0f / 255.0f, 26.0f / 255.0f, 29.0f / 255.0f, 1.f);
    glDrawArrays(GL_LINES, 0, 4); // x and y axes
    program_->setColor(22.0f / 255.0f, 26.0f / 255.0f, 29.0f / 255.0f, 0.25f);
    glDrawArrays(GL_LINES, 4, static_cast<int>(data_->count())); // grid
}

void CartesianRenderer::changeArea(const Area& area) const {
    data_->buildGrid(area, gridSize_);
}
