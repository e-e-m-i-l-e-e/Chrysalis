#include "CartesianRendererData.h"

#include <cmath>

using namespace Chrysalis;

void CartesianRendererData::buildGrid(const Area& area, const float gridSize) {
    const float xFrom = std::floor(area.x() / gridSize) * gridSize;
    const float xRange = std::ceil(area.width() / gridSize + 1) * gridSize;

    const float yFrom = std::floor(area.y() / gridSize) * gridSize;
    const float yRange = std::ceil(area.height() / gridSize + 1) * gridSize;

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
        shift += gridSize;
    }

    // y-lines
    shift = 0.f;
    while (shift <= yRange) {
        data_.emplace_back(xFrom, yFrom + shift);
        data_.emplace_back(xFrom + xRange, yFrom + shift);
        shift += gridSize;
    }

    updateVBO();
}

size_t CartesianRendererData::count() {
    return data_.size();
}

Vertex2f* CartesianRendererData::vbo() {
    return data_.data();
}
