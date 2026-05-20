#include "CartesianRenderer.h"

#include <iostream>

void CartesianRenderer::changeArea(const QRectF& area) {
    std::cout << "New area: x = " << area.x() << " y = " << area.y() << " width = " << area.width() << " height = " << area.height() << std::endl;
    if (area.x() != area_.x()) {

    }
    if (area.y() != area_.y()) {

    }
    if (area.width() != area_.width()) {

    }
    if (area.height() != area_.height()) {

    }
    area_ = area;
}

void CartesianRenderer::draw() {

}
