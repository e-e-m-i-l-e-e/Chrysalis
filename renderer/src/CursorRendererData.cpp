#include "CursorRendererData.h"

using namespace Chrysalis;

void CursorRendererData::projectCursor(const Vertex2f& cursor) {
    data_.clear();
    // x axis
    data_.emplace_back(cursor.x(), 0.f, 0.f);
    data_.emplace_back(cursor.x(), cursor.y(), cursor.y());
    // y axis
    data_.emplace_back(0.f, cursor.y(), 0.f);
    data_.emplace_back(cursor.x(), cursor.y(), cursor.x());

    updateVBO();
}

size_t CursorRendererData::count() {
    return data_.size();
}

Vertex3f* CursorRendererData::vbo() {
    return data_.data();
}
