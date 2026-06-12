#include "BaseOpenGLProgram.h"

#include <fstream>

#include "Logging.h"
#define LOGGER_NAME "OpenGL Program"

using namespace Chrysalis;

BaseOpenGLProgram::BaseOpenGLProgram(const char* vertexShader, const char* fragmentShader)
    : vertexShader_(vertexShader), fragmentShader_(fragmentShader) {}

BaseOpenGLProgram::~BaseOpenGLProgram() {
    glDeleteProgram(program_);
}

GLint BaseOpenGLProgram::prepareShader(const char* shaderCode, const GLenum shaderType) {
    const GLint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(static_cast<size_t>(len));
        glGetShaderInfoLog(shader, len, nullptr, log.data());
        glDeleteShader(shader);

        LOG_CRITICAL("Failed to compile vertex shader. Error log: {}.", log.data());
    }
    return shader;
}

void BaseOpenGLProgram::initialize() {
    const GLint vertexShader = prepareShader(vertexShader_, GL_VERTEX_SHADER);
    const GLint fragmentShader = prepareShader(fragmentShader_, GL_FRAGMENT_SHADER);

    program_ = glCreateProgram();
    glAttachShader(program_, vertexShader);
    glAttachShader(program_, fragmentShader);
    glLinkProgram(program_);

    GLint ok = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(static_cast<size_t>(len));
        glGetProgramInfoLog(program_, len, nullptr, log.data());
        glDeleteProgram(program_);
        program_ = 0;

        LOG_CRITICAL("Failed to link OpenGL program. Error log: {}.", log.data());
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void BaseOpenGLProgram::bind() const {
    glUseProgram(program_);
}

void BaseOpenGLProgram::release() {
    glUseProgram(0);
}

void BaseOpenGLProgram::setUniformValue(const char* name, const GLint value) const {
    glUniform1i(glGetUniformLocation(program_, name), value);
}

void BaseOpenGLProgram::setUniformValue(const char* name, const GLfloat value) const {
    glUniform1f(glGetUniformLocation(program_, name), value);
}

void BaseOpenGLProgram::setUniformValue(const char* name, const glm::mat4x4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(program_, name), 1, GL_FALSE, &value[0][0]);
}

void BaseOpenGLProgram::setUniformValue(const char* name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w) const {
    glUniform4f(glGetUniformLocation(program_, name), x, y, z, w);
}
