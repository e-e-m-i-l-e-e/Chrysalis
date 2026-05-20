#ifndef FASHIONDESIGNAPPS_CARTESIANRENDERER_H
#define FASHIONDESIGNAPPS_CARTESIANRENDERER_H

#include <QRectF>

#include "BaseRenderer.h"
#include "Vertex.h"

class CartesianRenderer: public BaseRenderer<Vertex> {
public:
    void render() override;
    void initialize() override;
    void changeArea(const QRectF& area);
private:
    float gridSize_ = 100;
    std::vector<float> grid;
};

#endif //FASHIONDESIGNAPPS_CARTESIANRENDERER_H