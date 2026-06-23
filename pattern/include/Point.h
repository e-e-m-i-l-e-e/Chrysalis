#ifndef CHRYSALIS_POINT_H
#define CHRYSALIS_POINT_H

#include "config.h"
#include "observers/PointObserver.h"
#include "observers/BaseObservable.h"

namespace Chrysalis {
    class Point: public BaseObservable<PointObserver> {
    public:
        Point(const CGAL::Point& point);
        explicit Point(double x, double y);

        const double& x() const;
        const double& y() const;

        void move(CGAL::Point point);

        operator const CGAL::Point&() const;
        operator const CGAL::CPoint() const;

        CGAL::Vector operator-(const Point& other) const;
        CGAL::Point operator+(const CGAL::Vector& vector) const;
    private:
        CGAL::Point point_;
    };
}

#endif //CHRYSALIS_POINT_H