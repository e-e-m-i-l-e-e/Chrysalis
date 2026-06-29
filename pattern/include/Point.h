#ifndef CHRYSALIS_POINT_H
#define CHRYSALIS_POINT_H

#include "CGAL.h"
#include "observers/PointObserver.h"
#include "observers/BaseObservable.h"

namespace Chrysalis {
    class Point: public BaseObservable<PointObserver> {
    public:
        Point(const CG::Point& point);
        explicit Point(double x, double y);

        const double& x() const;
        const double& y() const;

        void move(CG::Point point);

        operator const CG::Point&() const;
        operator const CG::CPoint() const;

        CG::Vector operator-(const Point& other) const;
        CG::Point operator+(const CG::Vector& vector) const;
    private:
        CG::Point point_;
    };
}

#endif //CHRYSALIS_POINT_H