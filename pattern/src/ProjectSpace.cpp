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

double ProjectSpace::angle(const Point& pointFrom, const Point& pointTo) {
    const CGAL::Vector v = pointFrom - pointTo;
    return std::atan2(CGAL::to_double(v.y()), CGAL::to_double(v.x())) * 180.0 / CGAL_PI;
}

double ProjectSpace::length(const Point& pointFrom, const Point& pointTo) {
    const CGAL::Vector v = pointFrom - pointTo;
    return std::sqrt(CGAL::to_double(v.squared_length()));
}

boost::optional<CGAL::Point> ProjectSpace::intersection(const CGAL::Line& line, const Point& pointFrom, const Point& pointTo) {
    const auto intersection = CGAL::intersection(CGAL::Line(pointFrom, pointTo), line);
    if (!intersection) return boost::none;
    const CGAL::Point* point = std::get_if<CGAL::Point>(&*intersection);
    return point ? boost::optional<CGAL::Point>(*point) : boost::none;
}

boost::optional<CGAL::Point> ProjectSpace::xIntersection(const Point& pointFrom, const Point& pointTo) {
    static CGAL::Line xAxis(Point(0, 0), Point(1, 0));
    return intersection(xAxis, pointFrom, pointTo);
}

boost::optional<CGAL::Point> ProjectSpace::yIntersection(const Point& pointFrom, const Point& pointTo) {
    static CGAL::Line yAxis(CGAL::Point(0, 0), CGAL::Point(0, 1));
    return intersection(yAxis, pointFrom, pointTo);
}
