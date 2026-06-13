#include "PatternSpaceRendererData.h"

void PatternSpaceRendererData::addPoint(const Point* point) {
    points_.emplace_back(point->x(), point->y(), 0);
    updateVBO();
}

size_t PatternSpaceRendererData::count() {
    return points_.size();
}

Vertex3f* PatternSpaceRendererData::vbo() {
    return points_.data();
}
