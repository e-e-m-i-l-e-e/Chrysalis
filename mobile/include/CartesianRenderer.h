#ifndef FASHIONDESIGNAPPS_CARTESIANRENDERER_H
#define FASHIONDESIGNAPPS_CARTESIANRENDERER_H

#include "Vertex.h"
#include "BaseRenderer.h"
#include "ChrysalisOpenGLProgram.h"

class CartesianRenderer: public BaseRenderer<Vertex> {
public:
    explicit CartesianRenderer(ChrysalisOpenGLProgram* program);

    void render() override;
    void changeArea(const QRectF& area);
private:
    float gridSize_ = 10;

    ChrysalisOpenGLProgram* program_;
};

#endif //FASHIONDESIGNAPPS_CARTESIANRENDERER_H