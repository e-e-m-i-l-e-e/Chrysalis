#include "Point.h"

using namespace Chrysalis;

Point::Point(double x, double y): point_(x, y) {}

Point::Point(const CGAL::Point& point): Point(point.x(), point.y()) {}

const double& Point::x() const {
    return point_.x();
}

const double& Point::y() const {
    return point_.y();
}

void Point::move(double x, double y) {
    point_ = CGAL::Point(x, y);
    notify(&PointObserver::pointMoved, this);
}

Point::operator const CGAL::Point&() const {
    return point_;
}

CGAL::Vector Point::operator-(const Point& other) const {
    return point_ - other.point_;
}

CGAL::Point Point::operator+(const CGAL::Vector& vector) const {
    return point_ + vector;
}
