#include "ChrysalisOpenGLProgram.h"

ChrysalisOpenGLProgram::ChrysalisOpenGLProgram()
: BaseOpenGLProgram(":/shaders/vertex.vert", ":/shaders/fragment.frag") {}

void ChrysalisOpenGLProgram::setPointRadius(const float radius) {
    setUniformValue("uPointRadius", radius);
}

void ChrysalisOpenGLProgram::setProjection(const QMatrix4x4& projection) {
    setUniformValue("uProjection", projection);
}

void ChrysalisOpenGLProgram::setColor(const float r, const float g, const float b, const float a) {
    setUniformValue("uColor", r, g, b, a);
}
