#include "BaseOpenGLProgram.h"

#include "Logger.h"
#define LOGGER_NAME "OpenGL Program"

BaseOpenGLProgram::BaseOpenGLProgram(const char* pathToVertexShader, const char* pathToFragmentShader)
: pathToVertexShader_(pathToVertexShader), pathToFragmentShader_(pathToFragmentShader) {}

void BaseOpenGLProgram::initialize() {
    QOpenGLShader vertexShader {QOpenGLShader::Vertex};
    QOpenGLShader fragmentShader {QOpenGLShader::Fragment};

    if (!vertexShader.compileSourceFile(pathToVertexShader_)) {
        LOG_CRITICAL("Failed to compile vertex shader. Error log: {}.", vertexShader.log().toStdString());
    }
    if (!fragmentShader.compileSourceFile(pathToFragmentShader_)) {
        LOG_CRITICAL("Failed to compile fragment shader. Error log: {}.", fragmentShader.log().toStdString());
    }
    if (!program_.addShader(&vertexShader)) {
        LOG_CRITICAL("Failed to add vertex shader. Error log: {}.", program_.log().toStdString());
    }
    if (!program_.addShader(&fragmentShader)) {
        LOG_CRITICAL("Failed to add fragment shader. Error log: {}.", program_.log().toStdString());
    }
    if (!program_.link()) {
        LOG_CRITICAL("Failed to link OpenGL program. Error log: {}.", program_.log().toStdString());
    }
}

void BaseOpenGLProgram::bind() {
    program_.bind();
}

void BaseOpenGLProgram::release() {
    program_.release();
}

void BaseOpenGLProgram::setUniformValue(const char* name, const GLint value) {
    program_.setUniformValue(name, value);
}

void BaseOpenGLProgram::setUniformValue(const char* name, const GLfloat value) {
    program_.setUniformValue(name, value);
}

void BaseOpenGLProgram::setUniformValue(const char* name, const QMatrix4x4& value) {
    program_.setUniformValue(name, value);
}

void BaseOpenGLProgram::setUniformValue(const char* name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w) {
    program_.setUniformValue(name, x, y, z, w);
}
