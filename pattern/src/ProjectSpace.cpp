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

Point* ProjectSpace::addPoint(const Point* pointFrom, double angle, const double length) {
    angle = angle * CGAL_PI / 180;
    const auto point = new Point(pointFrom->x() + length * std::cos(angle), pointFrom->y() + length * std::sin(angle));
    points_.insert(point);
    return point;
}

double ProjectSpace::angle(const Point* pointFrom, const Point* pointTo) {
    const CGAL::Vector v = *pointFrom - *pointTo;
    return std::atan2(CGAL::to_double(v.y()), CGAL::to_double(v.x())) * 180.0 / CGAL_PI;
}

double ProjectSpace::length(const Point* pointFrom, const Point* pointTo) {
    const CGAL::Vector v = *pointFrom - *pointTo;
    return std::sqrt(CGAL::to_double(v.squared_length()));
}
