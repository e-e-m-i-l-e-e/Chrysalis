#ifndef CHRYSALIS_CONFIG_H
#define CHRYSALIS_CONFIG_H

#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

namespace CGAL {
    static constexpr auto PRECISION = 15;

    using LinearKernel = Exact_predicates_inexact_constructions_kernel;
    using CircularKernel = Exact_circular_kernel_2;

    using Ray = Ray_2<LinearKernel>;
    using Line = Line_2<LinearKernel>;
    using Point = Point_2<LinearKernel>;
    using Vector = Vector_2<LinearKernel>;
    using Segment = Segment_2<LinearKernel>;

    using CPoint = Point_2<CircularKernel>;
    using Circle = Circle_2<CircularKernel>;
    using CArcPoint = Circular_arc_point_2<CircularKernel>;

    using CCIntersection = CK2_Intersection_traits<CircularKernel, Circle, Circle>::type;
}

#endif //CHRYSALIS_CONFIG_H