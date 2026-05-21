#include "CursorRenderer.h"

CursorRenderer::CursorRenderer(ChrysalisOpenGLProgram* program): program_(program) {}

void CursorRenderer::render() {
    vao.bind();
    program_->setColor(0.f, 1.f, 0.f, 1.f);
    glDrawArrays(GL_LINES, 0, data_.size());
    vao.release();
}

void CursorRenderer::changeCursor(const QPointF& cursor) {
    cursor_ = cursor;
    data_.clear();
    // x axis
    data_.emplace_back(cursor.x(), 0, 0);
    data_.emplace_back(cursor.x(), cursor.y(), cursor.y());
    // y axis
    data_.emplace_back(0, cursor.y(), 0);
    data_.emplace_back(cursor.x(), cursor.y(), cursor.x());
    shouldUpload();
}
