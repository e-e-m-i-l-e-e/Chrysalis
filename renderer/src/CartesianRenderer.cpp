#include "CartesianRenderer.h"

#include <iostream>

using namespace Chrysalis;

CartesianRenderer::CartesianRenderer(MainOpenGLProgram* program): program_(program) {}

void CartesianRenderer::draw() {
    program_->setColor(22.0f / 255.0f, 26.0f / 255.0f, 29.0f / 255.0f, 1.f);
    glDrawArrays(GL_LINES, 0, 4); // x and y axes
    program_->setColor(22.0f / 255.0f, 26.0f / 255.0f, 29.0f / 255.0f, 0.25f);
    glDrawArrays(GL_LINES, 4, static_cast<int>(data_.size()) - 4); // grid
}

void CartesianRenderer::changeArea(const Area& area) {
    const float xFrom = std::floor(area.x() / gridSize_) * gridSize_;
    const float xRange = std::ceil(area.width() / gridSize_ + 1) * gridSize_;

    const float yFrom = std::floor(area.y() / gridSize_) * gridSize_;
    const float yRange = std::ceil(area.height() / gridSize_ + 1) * gridSize_;

    data_.clear();
    // x axis
    data_.emplace_back(0.f, yFrom);
    data_.emplace_back(0.f, yFrom + yRange);
    // y axis
    data_.emplace_back(xFrom, 0.f);
    data_.emplace_back(xFrom + xRange, 0.f);

    // x-lines
    float shift = 0.f;
    while (shift <= xRange) {
        data_.emplace_back(xFrom + shift, yFrom);
        data_.emplace_back(xFrom + shift, yFrom + yRange);
        shift += gridSize_;
    }

    // y-lines
    shift = 0.f;
    while (shift <= yRange) {
        data_.emplace_back(xFrom, yFrom + shift);
        data_.emplace_back(xFrom + xRange, yFrom + shift);
        shift += gridSize_;
    }

    shouldUpload();
}
