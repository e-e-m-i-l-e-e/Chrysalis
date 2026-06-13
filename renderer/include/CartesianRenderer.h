#ifndef CHRYSALIS_CARTESIANRENDERER_H
#define CHRYSALIS_CARTESIANRENDERER_H

#include "Area.h"
#include "BaseRenderer.h"
#include "CartesianRendererData.h"
#include "MainOpenGLProgram.h"

namespace Chrysalis {
    class CartesianRenderer: public BaseRenderer<CartesianRendererData> {
    public:
        explicit CartesianRenderer(MainOpenGLProgram* program, CartesianRendererData* data);

        void draw() override;
        void changeArea(const Area& area) const;
    private:
        float gridSize_ = 10;

        MainOpenGLProgram* program_;
    };
}

#endif //CHRYSALIS_CARTESIANRENDERER_H