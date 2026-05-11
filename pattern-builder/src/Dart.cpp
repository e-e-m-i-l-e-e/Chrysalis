#include "Dart.h"

Dart::Dart(Space* space): space_(space) {}

void Dart::addPoint(const std::string& pointName) {
    polygon_.push_back(space_->getPoint(pointName));
}

Polygon& Dart::getPolygon() {
    return polygon_;
}
