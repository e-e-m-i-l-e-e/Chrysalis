#ifndef FASHIONDESIGNAPPS_BASEOPENGLPROGRAM_H
#define FASHIONDESIGNAPPS_BASEOPENGLPROGRAM_H

#include <QOpenGLShaderProgram>

class BaseOpenGLProgram {
public:
    void bind();
    void release();
    void initialize();
protected:
    explicit BaseOpenGLProgram(const char* pathToVertexShader, const char* pathToFragmentShader);

    void setUniformValue(const char *name, GLint value);
    void setUniformValue(const char *name, GLfloat value);
    void setUniformValue(const char *name, const QMatrix4x4& value);
    void setUniformValue(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
private:
    const char* pathToVertexShader_;
    const char* pathToFragmentShader_;

    QOpenGLShaderProgram program_;
};

#endif //FASHIONDESIGNAPPS_BASEOPENGLPROGRAM_H