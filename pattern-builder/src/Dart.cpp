#include "Dart.h"

using namespace PB;

Dart::Dart(Space* space): space_(space) {}

void Dart::addPoint(const std::string& pointName) {
    polygon_.push_back(space_->getPoint(pointName));
}

Polygon& Dart::getPolygon() {
    return polygon_;
}

std::vector<float> Dart::getPoints() {
    int i = 0;
    std::vector<float> points(polygon_.size() * 2);
    for (const auto& point: polygon_) {
        points[i] = point.x();
        points[i + 1] = point.y();
        i += 2;
    }
    return points;
}
