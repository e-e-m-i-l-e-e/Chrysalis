#include "ProjectSpace.h"

#include "CGAL/number_type_config.h"

using namespace Chrysalis;

ProjectSpace::~ProjectSpace() {
    for (auto& point : points_) {
        delete point;
    }
}

Point* ProjectSpace::addPoint(double x, double y) {
    const auto point = new Point(x, y);
    points_.insert(point);
    return point;
}

Point* ProjectSpace::addPoint(const Point* fromPoint, double angle, const double length) {
    angle = angle * CGAL_PI / 180;
    const auto point = new Point(fromPoint->x() + length * std::cos(angle), fromPoint->y() + length * std::sin(angle));
    points_.insert(point);
    return point;
}