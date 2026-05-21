#ifndef FASHIONDESIGNAPPS_OPENGLPROGRAM_H
#define FASHIONDESIGNAPPS_OPENGLPROGRAM_H

#include "BaseOpenGLProgram.h"

class ChrysalisOpenGLProgram: public BaseOpenGLProgram {
public:
    explicit ChrysalisOpenGLProgram();

    void setPointRadius(float radius);
    void setProjection(const QMatrix4x4& projection);
    void setColor(float r, float g, float b, float a);
};

#endif //FASHIONDESIGNAPPS_OPENGLPROGRAM_H