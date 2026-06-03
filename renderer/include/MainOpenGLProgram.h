#ifndef CHRYSALIS_OPENGLPROGRAM_H
#define CHRYSALIS_OPENGLPROGRAM_H

#include "BaseOpenGLProgram.h"

namespace Chrysalis {
    class MainOpenGLProgram: public BaseOpenGLProgram {
    public:
        explicit MainOpenGLProgram();

        void setPointRadius(float radius) const;
        void setProjection(const glm::mat4x4& projection) const;
        void setColor(float r, float g, float b, float a) const;
    };
}

#endif //CHRYSALIS_OPENGLPROGRAM_H