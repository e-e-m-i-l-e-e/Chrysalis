#include "CursorRendererData.h"

using namespace Chrysalis;

void CursorRendererData::projectCursor(const float x, const float y) {
    data_.clear();
    // x axis
    data_.emplace_back(x, 0.f, 0.f);
    data_.emplace_back(x, y, y);
    // y axis
    data_.emplace_back(0.f, y, 0.f);
    data_.emplace_back(x, y, x);

    updateVBO();
}

size_t CursorRendererData::size() {
    return data_.size();
}

std::vector<Vertex3f> CursorRendererData::vbo() {
    return data_;
}
