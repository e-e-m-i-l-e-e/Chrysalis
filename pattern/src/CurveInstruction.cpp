#include "instructions/CurveInstruction.h"

#include <tinysplinecxx.h>
#include <boost/math/quadrature/gauss_kronrod.hpp>
#include <cmath>
#include <optional>
#include <algorithm>
#include <ranges>
#include <vector>

using namespace Chrysalis;

CurveInstruction::CurveInstruction(ProjectSpace* space, args::patterns* patterns, const args::vector* from,
                                   const args::vector* to,
                                   const args::container<PatternPointArgument>* points) :
    BasePatternInstruction(space, patterns), from_(from), to_(to), points_(points) {}

CurveInstruction::~CurveInstruction() {
    delete from_;
    delete to_;
    delete points_;
}

bool CurveInstruction::isValid() {
    return from_->isValid() && to_->isValid();
}

struct Vec2 { double x, y; };

static Vec2 normalize(const Vec2& v) {
    double len = std::sqrt(v.x * v.x + v.y * v.y);
    return { v.x / len, v.y / len };
}

void CurveInstruction::execute() {
    const auto segmentFrom = static_cast<CG::Segment>(*from_);
    const auto segmentTo = static_cast<CG::Segment>(*to_);

    std::vector<tinyspline::real> points;
    points.reserve((points_->count() + 4) * 2);
    points.push_back(segmentFrom.end().x());
    points.push_back(segmentFrom.end().y());
    points.push_back(segmentFrom.end().x());
    points.push_back(segmentFrom.end().y() - 0.1);
    for (const auto& point: *points_) {
        points.push_back(point->get()->x());
        points.push_back(point->get()->y());
    }
    points.push_back(segmentTo.end().x() - 0.1);
    points.push_back(segmentTo.end().y());
    points.push_back(segmentTo.end().x());
    points.push_back(segmentTo.end().y());

    const auto spline = tinyspline::BSpline::interpolateCubicNatural(points, 2);
    const auto derivative = spline.derive();

    auto evalPoint = [&](const double u) {
        tinyspline::Vec2 v = spline.eval(u).resultVec2();
        return std::pair<double,double>{v.x(), v.y()};
    };

    auto evalDeriv = [&](const double u) {
        tinyspline::Vec2 v = derivative.eval(static_cast<tinyspline::real>(u)).resultVec2();
        return std::pair<double,double>{v.x(), v.y()};
    };
    auto arcSpeed = [&](const double u) {
        auto [dx, dy] = evalDeriv(u);
        return std::sqrt(dx * dx + dy * dy);
    };

    // Find parameter u where the spline passes through (tx, ty) — coarse scan + Newton refine
    auto solveParam = [&](double tx, double ty, double lo) {
        constexpr int kSamples = 40;
        double bestU = lo, bestD = std::numeric_limits<double>::max();
        for (int s = 0; s <= kSamples; ++s) {
            double u = lo + (1 - lo) * s / kSamples;
            auto [px, py] = evalPoint(u);
            double d = (px - tx) * (px - tx) + (py - ty) * (py - ty);
            if (d < bestD) { bestD = d; bestU = u; }
        }
        double u = bestU;
        for (int iter = 0; iter < 30; ++iter) {
            auto [px, py] = evalPoint(u);
            auto [vx, vy] = evalDeriv(u);
            double fx = px - tx, fy = py - ty;
            double denom = vx * vx + vy * vy;
            if (denom < 1e-14) break;
            double du = (fx * vx + fy * vy) / denom;
            double newU = std::clamp(u - du, lo, 1.);
            if (std::abs(newU - u) < 1e-12) { u = newU; break; }
            u = newU;
        }
        return u;
    };

    // Arc-length resampling between each pair of consecutive real anchor points
    std::vector<std::pair<double,double>> anchors;
    for (int i = 0; i < points.size(); i += 2) {
        anchors.emplace_back(points[i], points[i + 1]);
    }
    std::vector<std::pair<double,double>> curvePoints = anchors;
    double start = solveParam(anchors.front().first, anchors.front().second, 0);
    size_t insertOffset = 0;

    for (size_t i = 1; i < anchors.size(); ++i) {
        auto [tx, ty] = anchors[i];
        double intersection = solveParam(tx, ty, start);

        double length = std::abs(boost::math::quadrature::gauss_kronrod<double, 15>::integrate(
            arcSpeed, start, intersection));

        int count = static_cast<int>(length / 0.5);   // <-- confirm this member name
        if (count > 2) {
            std::vector<std::pair<double,double>> extra;
            extra.reserve(count - 2);
            for (int k = 1; k < count - 1; ++k) {
                double u = start + (intersection - start) * (double(k) / (count - 1));
                extra.push_back(evalPoint(u));
            }
            size_t insertPos = i + insertOffset;
            curvePoints.insert(curvePoints.begin() + insertPos, extra.begin(), extra.end());
            insertOffset += extra.size();
        }
        start = intersection;
    }
    for (const auto& [x, y]: curvePoints) {
        for (const auto& p: *patterns_) {
            p->notify(&PatternSpaceObserver::pointAdded, new Point(x, y));
        }
        std::cout << x << " " << y << std::endl;
    }
}
