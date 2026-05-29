#ifndef CHRYSALIS_CARTESIANRENDERER_H
#define CHRYSALIS_CARTESIANRENDERER_H

#include "Vertex.h"
#include "BaseRenderer.h"
#include "ChrysalisOpenGLProgram.h"

class CartesianRenderer: public BaseRenderer<Vertex> {
public:
    explicit CartesianRenderer(ChrysalisOpenGLProgram* program);

    void draw() override;
    void changeArea(const QRectF& area);
private:
    float gridSize_ = 10;

    ChrysalisOpenGLProgram* program_;
};

#endif //CHRYSALIS_CARTESIANRENDERER_H