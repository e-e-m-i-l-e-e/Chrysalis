#ifndef CHRYSALIS_BASEOPENGLPROGRAM_H
#define CHRYSALIS_BASEOPENGLPROGRAM_H

#include <glad/gl.h>
#include <glm/mat4x4.hpp>

namespace Chrysalis {
    class BaseOpenGLProgram {
    public:
        ~BaseOpenGLProgram();
        void initialize();

        void bind() const;
        static void release();
    protected:
        explicit BaseOpenGLProgram(const char* vertexShader, const char* fragmentShader);

        void setUniformValue(const char *name, GLint value) const;
        void setUniformValue(const char *name, GLfloat value) const;
        void setUniformValue(const char *name, const glm::mat4x4& value) const;
        void setUniformValue(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
    private:
        static GLint prepareShader(const char* shaderCode, GLenum shaderType);

        const char* vertexShader_;
        const char* fragmentShader_;

        GLint program_ = 0;
    };
}

#endif //CHRYSALIS_BASEOPENGLPROGRAM_H