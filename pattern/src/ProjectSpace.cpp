#include "ProjectSpace.h"

using namespace Chrysalis;

ProjectSpace::~ProjectSpace() {
    for (auto& point : points_) {
        delete point;
    }
}

double ProjectSpace::sin(const double value) {
    return round(std::sin(value));
}

double ProjectSpace::cos(const double value) {
    return round(std::cos(value));
}

double ProjectSpace::radians(const double degrees) {
    return degrees * CGAL_PI / 180;
}

double ProjectSpace::round(const double value) {
    static double factor = std::pow(10.0, CGAL::PRECISION);
    return std::round(value * factor) / factor;
}

void ProjectSpace::movePoint(const Point* point, const CGAL::Point position) const {
    if (const auto p = const_cast<Point*>(point); points_.contains(p)) p->move(position);
}

Point* ProjectSpace::addPoint(const double x, const double y) {
    return addPoint({x, y});
}

Point* ProjectSpace::addPoint(const CGAL::Point& point) {
    const auto p = new Point(point);
    points_.insert(p);
    return p;
}

CGAL::Vector ProjectSpace::rotate(const CGAL::Vector& vector, double angle) {
    angle = angle * CGAL_PI / 180;
    return CGAL::Aff_transformation_2<CGAL::LinearKernel>(CGAL::ROTATION, sin(angle), cos(angle))(vector);
}

double ProjectSpace::angle(const CGAL::Vector& vector1, const CGAL::Vector& vector2) {
    return std::abs(std::atan2(vector1.y(), vector1.x()) - std::atan2(vector2.y(), vector2.x())) * 180.0 / CGAL_PI;
}

double ProjectSpace::angle(const CGAL::Point& pointFrom, const CGAL::Point& pointTo) {
    const CGAL::Vector v = pointTo - pointFrom;
    return std::atan2(CGAL::to_double(v.y()), CGAL::to_double(v.x())) * 180.0 / CGAL_PI;
}

double ProjectSpace::length(const CGAL::Point& pointFrom, const CGAL::Point& pointTo) {
    const CGAL::Vector v = pointFrom - pointTo;
    return std::sqrt(CGAL::to_double(v.squared_length()));
}

CGAL::Point ProjectSpace::relativePoint(const CGAL::Point& pointFrom, double angle, double length) {
    angle = angle * CGAL_PI / 180;
    return CGAL::Point(pointFrom.x() + length * cos(angle), pointFrom.y() + length * sin(angle));
}

boost::optional<CGAL::Point> ProjectSpace::xIntersection(const CGAL::Point& pointFrom, const CGAL::Point& pointTo) {
    static CGAL::Line xAxis(Point(0, 0), Point(1, 0));
    return intersection(xAxis, CGAL::Line(pointFrom, pointTo));
}

boost::optional<CGAL::Point> ProjectSpace::yIntersection(const CGAL::Point& pointFrom, const CGAL::Point& pointTo) {
    static CGAL::Line yAxis(CGAL::Point(0, 0), CGAL::Point(0, 1));
    return intersection(yAxis, CGAL::Line(pointFrom, pointTo));
}

CGAL::Point ProjectSpace::circlesIntersection(const CGAL::Point& anchor,
                                              CGAL::CPoint center1, const double radius1,
                                              CGAL::CPoint center2, const double radius2) {
    const CGAL::Circle circle1(center1, pow(radius1, 2));
    const CGAL::Circle circle2(center2, pow(radius2, 2));

    std::vector<CGAL::CCIntersection> intersections;
    CGAL::intersection(circle1, circle2, std::back_inserter(intersections));

    CGAL::Point intersectionPoint;
    double minSDistance = std::numeric_limits<double>::max();
    for (const auto& intersection : intersections) {
        const auto point = std::get<std::pair<CGAL::CArcPoint, unsigned int>>(intersection).first;
        const double x = CGAL::to_double(point.x());
        const double y = CGAL::to_double(point.y());
        if (const double distance = pow(x - anchor.x(), 2) + pow(y - anchor.y(), 2); distance < minSDistance) {
            minSDistance = distance;
            intersectionPoint = CGAL::Point(x, y);
        }
    }
    return intersectionPoint;
}
