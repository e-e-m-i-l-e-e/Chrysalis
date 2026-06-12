#ifndef CHRYSALIS_CARTESIANRENDERER_H
#define CHRYSALIS_CARTESIANRENDERER_H

#include "Area.h"
#include "Vertex2f.h"
#include "BaseRenderer.h"
#include "MainOpenGLProgram.h"

namespace Chrysalis {
    class CartesianRenderer: public BaseRenderer<Vertex2f> {
    public:
        explicit CartesianRenderer(MainOpenGLProgram* program);

        void draw() override;
        void changeArea(const Area& area);
    private:
        float gridSize_ = 10;

        MainOpenGLProgram* program_;
    };
}

#endif //CHRYSALIS_CARTESIANRENDERER_H