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

#include <tinysplinecxx.h>
#include <boost/math/quadrature/gauss_kronrod.hpp>
#include <cmath>
#include <limits>
#include <algorithm>

void CurveInstruction::execute() {
    const auto segmentFrom = static_cast<CG::Segment>(*from_);
    const auto segmentTo = static_cast<CG::Segment>(*to_);

    // Attachment points: where the curve actually starts/ends
    const double A0x = segmentFrom.end().x(), A0y = segmentFrom.end().y();
    const double ANx = segmentTo.end().x(),   ANy = segmentTo.end().y();   // <- was segmentTo.start()

    // Far points: define direction + weight (length) of the tangent handle
    const double B0x = segmentFrom.start().x(), B0y = segmentFrom.start().y();
    const double BNx = segmentTo.start().x(),   BNy = segmentTo.start().y(); // <- was segmentTo.end()

    // Mirror-reflect each segment about its attachment point
    const double H0x = 2 * A0x - B0x, H0y = 2 * A0y - B0y;
    const double HNx = 2 * ANx - BNx, HNy = 2 * ANy - BNy;

    // Build the anchor list: ONLY real points the curve must pass through
    std::vector<tinyspline::real> flat;
    flat.push_back(A0x); flat.push_back(A0y);
    for (const auto& point : *points_) {
        flat.push_back(point->get()->x());
        flat.push_back(point->get()->y());
    }
    flat.push_back(ANx); flat.push_back(ANy);

    const size_t numAnchors = flat.size() / 2;
    const size_t numSegments = numAnchors - 1;

    tinyspline::BSpline spline = tinyspline::BSpline::interpolateCubicNatural(flat, 2);

    // Override the boundary handles (P1 of first segment, P2 of last segment)
    // Layout per segment i: [P0x,P0y, P1x,P1y, P2x,P2y, P3x,P3y] at flat offset i*8
    std::vector<tinyspline::real> ctrlp = spline.controlPoints();

    ctrlp[2] = static_cast<tinyspline::real>(H0x);  // P1.x of segment 0
    ctrlp[3] = static_cast<tinyspline::real>(H0y);  // P1.y of segment 0

    const size_t lastBase = (numSegments - 1) * 8;
    ctrlp[lastBase + 4] = static_cast<tinyspline::real>(HNx);  // P2.x of last segment
    ctrlp[lastBase + 5] = static_cast<tinyspline::real>(HNy);  // P2.y of last segment

    spline.setControlPoints(ctrlp);

    // Recompute derivative AFTER editing control points
    const auto derivative = spline.derive();

    auto evalPoint = [&](double u) {
        tinyspline::Vec2 v = spline.eval(u).resultVec2();
        return std::pair<double,double>{v.x(), v.y()};
    };
    auto evalDeriv = [&](double u) {
        tinyspline::Vec2 v = derivative.eval(u).resultVec2();
        return std::pair<double,double>{v.x(), v.y()};
    };
    auto arcSpeed = [&](double u) {
        auto [dx, dy] = evalDeriv(u);
        return std::sqrt(dx * dx + dy * dy);
    };

    const double uMin = spline.domain().min();
    const double uMax = spline.domain().max();

    auto solveParam = [&](double tx, double ty, double lo, double hi) {
        constexpr int kSamples = 40;
        double bestU = lo, bestD = std::numeric_limits<double>::max();
        for (int s = 0; s <= kSamples; ++s) {
            double u = lo + (hi - lo) * s / kSamples;
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
            double newU = std::clamp(u - du, lo, hi);
            if (std::abs(newU - u) < 1e-12) { u = newU; break; }
            u = newU;
        }
        return u;
    };

    std::vector<std::pair<double,double>> anchors;
    for (size_t i = 0; i < flat.size(); i += 2) {
        anchors.emplace_back(flat[i], flat[i + 1]);
    }

    std::vector<std::pair<double,double>> curvePoints = anchors;
    double start = uMin;
    size_t insertOffset = 0;

    for (size_t i = 1; i < anchors.size(); ++i) {
        auto [tx, ty] = anchors[i];
        double intersection = solveParam(tx, ty, start, uMax);

        double length = std::abs(boost::math::quadrature::gauss_kronrod<double, 15>::integrate(
            arcSpeed, start, intersection));

        int count = static_cast<int>(length / 0.5);
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

    for (const auto& [x, y] : curvePoints) {
        for (const auto& p : *patterns_) {
            p->notify(&PatternSpaceObserver::pointAdded, new Point(x, y));
        }
    }
}
