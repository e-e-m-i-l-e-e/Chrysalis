#ifndef CHRYSALIS_POINT_H
#define CHRYSALIS_POINT_H

#include <CGAL/Simple_cartesian.h>

namespace CGAL {
    using Kernel = Simple_cartesian<double>;

    using Line = Line_2<Kernel>;
    using Point = Point_2<Kernel>;
    using Vector = Vector_2<Kernel>;
}

class Point {
public:
    Point(const CGAL::Point& point);
    explicit Point(double x, double y);

    const double& x() const;
    const double& y() const;

    operator const CGAL::Point&() const;
    CGAL::Vector operator-(const Point& other) const;
private:
    CGAL::Point point_;
};

#endif //CHRYSALIS_POINT_H