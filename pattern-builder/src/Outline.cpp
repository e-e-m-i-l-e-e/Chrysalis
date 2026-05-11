#include "Outline.h"

Outline::Outline(Space* space): space_(space) {}

Outline::~Outline() {
    for (const auto dart: darts_) {
        delete dart;
    }
}

void Outline::addPoint(const std::string& pointName) {
    polygon_.outer_boundary().push_back(space_->getPoint(pointName));
}

void Outline::addDart(Dart* dart) {
    darts_.push_front(dart);
    polygon_.add_hole(dart->getPolygon());
}

std::vector<float> Outline::getPoints() const {
    int i = 0;
    std::vector<float> points(polygon_.outer_boundary().size() * 2);
    for (const auto& point: polygon_.outer_boundary()) {
        points[i] = point.x();
        points[i + 1] = point.y();
        i += 2;
    }
    return points;
}
