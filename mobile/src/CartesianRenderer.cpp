#include "CartesianRenderer.h"

#include <iostream>

void CartesianRenderer::initialize() {
    BaseRenderer::initialize();
}

void CartesianRenderer::render() {
    vbo.bind();
    vbo.allocate(grid.data(), grid.size() * sizeof(float));
    vbo.release();

    vao.bind();
    // program_.setUniformValue("uColor", 1.f, 1.f, 1.f, 1.f);
    glDrawArrays(GL_LINES, 0, 4); // x and y axes
    // program_.setUniformValue("uColor", 1.f, 1.f, 1.f, 0.1f);
    glDrawArrays(GL_LINES, 4, grid.size() / 2 - 4); // grid
    vao.release();
}

void CartesianRenderer::changeArea(const QRectF& area) {
    std::cout << "ChangeArea: x = " << area.x() << " width = " << area.width() << " y = " << area.y() << " height = " << area.height() << std::endl;
    const float xFrom = std::floor(area.x() / gridSize_) * gridSize_;
    const float xRange = std::ceil(static_cast<float>(area.width()) / gridSize_) * gridSize_;

    const float yFrom = std::floor(area.y() / gridSize_) * gridSize_;
    const float yRange = std::ceil(static_cast<float>(area.height()) / gridSize_) * gridSize_;

    grid = {
        // x axis
        0.f, yFrom,
        0.f, yFrom + yRange,
        // y axis
        xFrom, 0.f,
        xFrom + xRange, 0.f
    };

    // x-lines
    for (int i = 0; i <= xRange; i += gridSize_) {
        grid.push_back(xFrom + i);
        grid.push_back(yFrom);
        grid.push_back(xFrom + i);
        grid.push_back(yFrom + yRange);
    }

    // y-lines
    for (int i = 0; i <= yRange; i += gridSize_) {
        grid.push_back(xFrom);
        grid.push_back(yFrom + i);
        grid.push_back(xFrom + xRange);
        grid.push_back(yFrom + i);
    }
}
