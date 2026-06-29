#include "Point.h"

using namespace Chrysalis;

Point::Point(double x, double y): point_(x, y) {}

Point::Point(const CG::Point& point): Point(point.x(), point.y()) {}

const double& Point::x() const {
    return point_.x();
}

const double& Point::y() const {
    return point_.y();
}

void Point::move(CG::Point position) {
    point_ = position;
    notify(&PointObserver::pointMoved, this);
}

Point::operator const CG::Point&() const {
    return point_;
}

Point::operator const CG::CPoint() const {
    static CGAL::Cartesian_converter<CG::LinearKernel, CG::CircularKernel> converter;
    return converter(point_);
}

CG::Vector Point::operator-(const Point& other) const {
    return point_ - other.point_;
}

CG::Point Point::operator+(const CG::Vector& vector) const {
    return point_ + vector;
}
