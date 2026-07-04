#ifndef CHRYSALIS_CURVE_H
#define CHRYSALIS_CURVE_H

#include <CGAL.h>
#include <tinysplinecxx.h>

namespace Chrysalis {
    class Curve {
    public:
        explicit Curve(CG::Point handleFrom, CG::Point handleTo, const std::vector<CG::Point>& points);
        [[nodiscard]] std::vector<CG::Point> curvePoints(double distance) const;
    private:
        tinyspline::BSpline spline_;
    };
}

#endif //CHRYSALIS_CURVE_H