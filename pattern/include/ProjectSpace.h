#ifndef CHRYSALIS_SPACE_H
#define CHRYSALIS_SPACE_H

#include <unordered_set>

#include "serialization.h"

#include "Point.h"

namespace Chrysalis {
    class ProjectSpace {
        SERIALIZED
    public:
        ~ProjectSpace();

        void movePoint(const Point* point, CG::Point position) const;

        Point* addPoint(double x, double y);
        Point* addPoint(const CG::Point& point);
    private:
        /// @uml{composition[1:*]}
        std::unordered_set<Point*> points_;
    };
}

#endif //CHRYSALIS_SPACE_H