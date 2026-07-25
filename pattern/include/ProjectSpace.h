#ifndef CHRYSALIS_SPACE_H
#define CHRYSALIS_SPACE_H

#include <unordered_set>

#include "Curve.h"
#include "serialization.h"

#include "Point.h"

namespace Chrysalis {
    class ProjectSpace {
        SERIALIZED
    public:
        ~ProjectSpace();

        void movePoint(const Point* point, CG::Point position) const;

        bool hasCurve(const Point* from, const Point* to) const;
        const Curve* getCurve(const Point* from, const Point* to) const;

        Point* addPoint(double x, double y);
        Point* addPoint(const CG::Point& point);
        Curve* addCurve(const Point* from, const Point* to,
                        const CG::Segment& segmentFrom, const CG::Segment& segmentTo,
                        const std::vector<CG::Point>& points);
    private:
        /// @uml{composition}
        std::unordered_set<Point*> points_;
        /// @uml{composition}
        std::unordered_map<const Point*, std::unordered_map<const Point*, Curve*>> curves_;
    };
}

#endif //CHRYSALIS_SPACE_H