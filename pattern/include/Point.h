#ifndef CHRYSALIS_POINT_H
#define CHRYSALIS_POINT_H

#include <CGAL/Simple_cartesian.h>

namespace CGAL {
    using Kernel = Simple_cartesian<double>;
    using Point = Point_2<Kernel>;
}

class Point {
public:
    explicit Point(double x, double y);

    const double& x() const;
    const double& y() const;
private:
    CGAL::Point point_;
};

#endif //CHRYSALIS_POINT_H