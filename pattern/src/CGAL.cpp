#include "CGAL.h"

using namespace Chrysalis;

double CG::sin(const double value) {
    return round(std::sin(value));
}

double CG::cos(const double value) {
    return round(std::cos(value));
}

double CG::radians(const double degrees) {
    return degrees * CGAL_PI / 180;
}

double CG::round(const double value) {
    static double factor = std::pow(10.0, PRECISION);
    return std::round(value * factor) / factor;
}

CG::Vector CG::rotate(const Vector& vector, double angle) {
    angle = angle * CGAL_PI / 180;
    return CGAL::Aff_transformation_2<LinearKernel>(CGAL::ROTATION, sin(angle), cos(angle))(vector);
}

double CG::angle(const Vector& vector1, const Vector& vector2) {
    return std::abs(std::atan2(vector1.y(), vector1.x()) - std::atan2(vector2.y(), vector2.x())) * 180.0 / CGAL_PI;
}

double CG::angle(const Point& pointFrom, const Point& pointTo) {
    const Vector v = pointTo - pointFrom;
    return std::atan2(CGAL::to_double(v.y()), CGAL::to_double(v.x())) * 180.0 / CGAL_PI;
}

double CG::length(const Point& pointFrom, const Point& pointTo) {
    const Vector v = pointFrom - pointTo;
    return std::sqrt(CGAL::to_double(v.squared_length()));
}

CG::Point CG::mirror(const Point& point, const Point& center) {
    return center + (center - point);
}

CG::Point CG::relativePoint(const Point& pointFrom, const Vector& vector) {
    return Point(pointFrom.x() + vector.x(), pointFrom.y() + vector.y());
}

CG::Point CG::relativePoint(const Point& pointFrom, double angle, double length) {
    angle = angle * CGAL_PI / 180;
    return Point(pointFrom.x() + length * cos(angle), pointFrom.y() + length * sin(angle));
}

CG::Point CG::projection(const Point& point, const Line& line) {
    return line.projection(point);
}

std::optional<CG::Point> CG::xIntersection(const Point& pointFrom, const Point& pointTo) {
    static Line xAxis(Point(0, 0), Point(1, 0));
    return CG::intersection(xAxis, Line(pointFrom, pointTo));
}

std::optional<CG::Point> CG::yIntersection(const Point& pointFrom, const Point& pointTo) {
    static Line yAxis(Point(0, 0), Point(0, 1));
    return CG::intersection(yAxis, Line(pointFrom, pointTo));
}

CG::Point CG::circlesIntersection(const Point& anchor,
                                              CPoint center1, const double radius1,
                                              CPoint center2, const double radius2) {
    const Circle circle1(center1, std::pow(radius1, 2));
    const Circle circle2(center2, std::pow(radius2, 2));

    std::vector<CCIntersection> intersections;
    CGAL::intersection(circle1, circle2, std::back_inserter(intersections));

    Point intersectionPoint;
    double minSDistance = std::numeric_limits<double>::max();
    for (const auto& intersection : intersections) {
        const auto point = std::get<std::pair<CArcPoint, unsigned int>>(intersection).first;
        const double x = CGAL::to_double(point.x());
        const double y = CGAL::to_double(point.y());
        if (const double distance = std::pow(x - anchor.x(), 2) + std::pow(y - anchor.y(), 2); distance < minSDistance) {
            minSDistance = distance;
            intersectionPoint = Point(x, y);
        }
    }
    return intersectionPoint;
}
