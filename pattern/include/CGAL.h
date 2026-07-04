#ifndef CHRYSALIS_CONFIG_H
#define CHRYSALIS_CONFIG_H

#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <optional>

namespace Chrysalis::CG {

    // --- Constants ---------------------------------------------------------------------------------------------------

    static constexpr auto PRECISION = 15;

    // --- CGAL Types --------------------------------------------------------------------------------------------------

    using LinearKernel = CGAL::Exact_predicates_inexact_constructions_kernel;
    using CircularKernel = CGAL::Exact_circular_kernel_2;

    using Ray = CGAL::Ray_2<LinearKernel>;
    using Line = CGAL::Line_2<LinearKernel>;
    using Point = CGAL::Point_2<LinearKernel>;
    using Vector = CGAL::Vector_2<LinearKernel>;
    using Segment = CGAL::Segment_2<LinearKernel>;

    using CPoint = CGAL::Point_2<CircularKernel>;
    using Circle = CGAL::Circle_2<CircularKernel>;
    using CArcPoint = CGAL::Circular_arc_point_2<CircularKernel>;

    using CCIntersection = CGAL::CK2_Intersection_traits<CircularKernel, Circle, Circle>::type;

    // === Functions ===================================================================================================

    double sin(double value);
    double cos(double value);
    double round(double value);
    double radians(double degrees);
    Vector rotate(const Vector& vector, double angle);
    double angle(const Vector& vector1, const Vector& vector2);
    double angle(const Point& pointFrom, const Point& pointTo);
    double length(const Point& pointFrom, const Point& pointTo);
    Point mirror(const Point& point, const Point& center);
    Point relativePoint(const Point& pointFrom, double angle, double length);
    Point projection(const Point& point, const Line& line);
    template<typename T1, typename T2>
    std::optional<Point> intersection(const T1& obj1, const T2& obj2) {
        const auto intersection = CGAL::intersection(obj1, obj2);
        if (!intersection) return std::nullopt;
        const Point* point = std::get_if<Point>(&*intersection);
        return point ? std::optional(*point) : std::nullopt;
    }
    std::optional<Point> xIntersection(const Point& pointFrom, const Point& pointTo);
    std::optional<Point> yIntersection(const Point& pointFrom, const Point& pointTo);
    Point circlesIntersection(const Point& anchor, CPoint center1, double radius1, CPoint center2, double radius2);

}

#endif //CHRYSALIS_CONFIG_H