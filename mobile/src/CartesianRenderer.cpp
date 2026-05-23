#include "CartesianRenderer.h"
CartesianRenderer::CartesianRenderer(ChrysalisOpenGLProgram* program): program_(program) {}

void CartesianRenderer::draw() {
    program_->setColor(22.0f / 255.0f, 26.0f / 255.0f, 29.0f / 255.0f, 0.05f);
    glDrawArrays(GL_LINES, 0, 4); // x and y axes
    program_->setColor(22.0f / 255.0f, 26.0f / 255.0f, 29.0f / 255.0f, 0.05f);
    glDrawArrays(GL_LINES, 4, data_.size() - 4); // grid
}

void CartesianRenderer::changeArea(const QRectF& area) {
    const float xFrom = std::floor(area.x() / gridSize_) * gridSize_;
    const float xRange = std::ceil(static_cast<float>(area.width()) / gridSize_ + 1) * gridSize_;

    const float yFrom = std::floor(area.y() / gridSize_) * gridSize_;
    const float yRange = std::ceil(static_cast<float>(area.height()) / gridSize_ + 1) * gridSize_;

    data_.clear();
    // x axis
    data_.emplace_back(0.f, yFrom);
    data_.emplace_back(0.f, yFrom + yRange);
    // y axis
    data_.emplace_back(xFrom, 0.f);
    data_.emplace_back(xFrom + xRange, 0.f);

    // x-lines
    for (int i = 0; i <= xRange; i += gridSize_) {
        data_.emplace_back(xFrom + i, yFrom);
        data_.emplace_back(xFrom + i, yFrom + yRange);
    }

    // y-lines
    for (int i = 0; i <= yRange; i += gridSize_) {
        data_.emplace_back(xFrom, yFrom + i);
        data_.emplace_back(xFrom + xRange, yFrom + i);
    }

    shouldUpload();
}
