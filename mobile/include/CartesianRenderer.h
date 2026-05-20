#ifndef FASHIONDESIGNAPPS_CARTESIANRENDERER_H
#define FASHIONDESIGNAPPS_CARTESIANRENDERER_H

#include <QRectF>

#include "BaseRenderer.h"

class CartesianRenderer: public BaseRenderer {
public:
    void changeArea(const QRectF& area);
    void draw() override;
private:
    QRectF area_;
    std::vector<float> xGrid;
    std::vector<float> yGrid;
};

#endif //FASHIONDESIGNAPPS_CARTESIANRENDERER_H