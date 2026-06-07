#include "CursorRenderer.h"

using namespace Chrysalis;

CursorRenderer::CursorRenderer(MainOpenGLProgram* program): program_(program) {}

void CursorRenderer::draw() {
    program_->setColor(1.f, 1.f, 1.f, opacity_);
    glDrawArrays(GL_LINES, 0, data_.size());
}

void CursorRenderer::hideCursor() {
    displayCursor_ = false;
}

void CursorRenderer::displayCursor(const Vertex2f& cursor) {
    displayCursor_ = true;

    data_.clear();
    // x axis
    data_.emplace_back(cursor.x(), 0.f, 0.f);
    data_.emplace_back(cursor.x(), cursor.y(), cursor.y());
    // y axis
    data_.emplace_back(0.f, cursor.y(), 0.f);
    data_.emplace_back(cursor.x(), cursor.y(), cursor.x());

    shouldUpload();
}

void CursorRenderer::prepareNextFrame(int64_t startTime, const int64_t previousFrameTime, const int64_t currentFrameTime) {
    static constexpr float duration = 300.f;
    const float target = displayCursor_ ? 1.f : 0.f;
    if (displayCursor_ && opacity_ < target) {
        // Cursor in
        opacity_ = std::min(target, opacity_ + (currentFrameTime - previousFrameTime) / duration);
    } else if (!displayCursor_ && opacity_ > target) {
        // Cursor out
        opacity_ = std::max(target, opacity_ - (currentFrameTime - previousFrameTime) / duration);
    }
    if (opacity_ == target) complete();
}
