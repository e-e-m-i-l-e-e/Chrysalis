#include "CursorRenderer.h"

CursorRenderer::CursorRenderer(ChrysalisOpenGLProgram* program): program_(program) {}

void CursorRenderer::draw() {
    program_->setColor(1.f, 1.f, 1.f, opacity_);
    glDrawArrays(GL_LINES, 0, data_.size());
}

void CursorRenderer::hideCursor() {
    displayCursor_ = false;
}

void CursorRenderer::displayCursor(const QPointF& cursor) {
    displayCursor_ = true;

    data_.clear();
    // x axis
    data_.emplace_back(cursor.x(), 0, 0);
    data_.emplace_back(cursor.x(), cursor.y(), cursor.y());
    // y axis
    data_.emplace_back(0, cursor.y(), 0);
    data_.emplace_back(cursor.x(), cursor.y(), cursor.x());

    shouldUpload();
}

void CursorRenderer::prepareNextFrame(const qint64 startTime, const qint64 previousFrameTime, const qint64 currentFrameTime) {
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
