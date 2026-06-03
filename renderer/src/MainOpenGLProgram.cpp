#include "MainOpenGLProgram.h"

#include "main_shaders.h"

using namespace Chrysalis;

MainOpenGLProgram::MainOpenGLProgram()
    : BaseOpenGLProgram(mainVertexShader, mainFragmentShader) {}

void MainOpenGLProgram::setPointRadius(const float radius) const {
    setUniformValue("uPointRadius", radius);
}

void MainOpenGLProgram::setProjection(const glm::mat4x4& projection) const {
    setUniformValue("uProjection", projection);
}

void MainOpenGLProgram::setColor(const float r, const float g, const float b, const float a) const {
    setUniformValue("uColor", r, g, b, a);
}
