#include "Curve.h"

using namespace Chrysalis;

Curve::Curve(const CG::Point handleFrom, const CG::Point handleTo, const std::vector<CG::Point>& points)
    : spline_([&] {
        std::vector<tinyspline::real> coordinates;
        coordinates.reserve(points.size() * 2);
        for (const auto& p : points) {
            coordinates.push_back(p.x());
            coordinates.push_back(p.y());
        }
        auto spline = tinyspline::BSpline::interpolateCubicNatural(coordinates, 2);

        const auto last = (points.size() * 2 - 4) * 4;
        auto controlPoints = spline.controlPoints();
        controlPoints[2] = handleFrom.x();
        controlPoints[3] = handleFrom.y();
        controlPoints[last + 4] = handleTo.x();
        controlPoints[last + 5] = handleTo.y();

        spline.setControlPoints(controlPoints);
        return spline;
    }()) {}

std::vector<CG::Point> Curve::curvePoints(const double distance) const {
    const int n = static_cast<int>(std::ceil(spline_.chordLengths().arcLength() / distance));
    std::vector<CG::Point> points(n + 1);
    for (int i = 0; i <= n; i++) {
        const auto res = spline_.eval(static_cast<double>(i) / n).resultVec2();
        points[i] = {res.x(), res.y()};
    }
    return points;
}
