#include "Point.h"

Point::Point(double x, double y): point_(x, y) {}

const double& Point::x() const {
    return point_.x();
}

const double& Point::y() const {
    return point_.y();
}

CGAL::Vector Point::operator-(const Point& other) const {
    return point_ - other.point_;
}
