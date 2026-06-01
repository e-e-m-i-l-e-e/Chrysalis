#ifndef CHRYSALIS_SPACE_H
#define CHRYSALIS_SPACE_H

#include <unordered_set>

#include "serialization.h"

#include "Point.h"

namespace Chrysalis {
    class SERIALIZABLE(ProjectSpace) {
        PROVIDE_SERIALIZATION_ACCESS(ProjectSpace)
    public:
        ~ProjectSpace();

        Point* addPoint(double x, double y);
        Point* addPoint(const Point* fromPoint, double angle, double length);
    private:
        /// @uml{composition[1:*]}
        std::unordered_set<Point*> points_;
    };
    SIMPLE_SERIALIZE_MEMBERS(ProjectSpace)
}

#endif //CHRYSALIS_SPACE_H