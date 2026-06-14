#ifndef CHRYSALIS_POINT_H
#define CHRYSALIS_POINT_H

#include "config.h"

class Point {
public:
    Point(const CGAL::Point& point);
    explicit Point(double x, double y);

    const double& x() const;
    const double& y() const;

    operator const CGAL::Point&() const;
    CGAL::Vector operator-(const Point& other) const;
    CGAL::Point operator+(const CGAL::Vector& vector) const;
private:
    CGAL::Point point_;
};

#endif //CHRYSALIS_POINT_H