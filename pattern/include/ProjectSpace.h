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
        Point* addPoint(const Point* pointFrom, double angle, double length);

        static double angle(const Point& pointFrom, const Point& pointTo);
        static double length(const Point& pointFrom, const Point& pointTo);
        static boost::optional<CGAL::Point> xIntersection(const Point& pointFrom, const Point& pointTo);
        static boost::optional<CGAL::Point> yIntersection(const Point& pointFrom, const Point& pointTo);
    private:
        static boost::optional<CGAL::Point> intersection(const CGAL::Line& line, const Point& pointFrom, const Point& pointTo);
        /// @uml{composition[1:*]}
        std::unordered_set<Point*> points_;
    };
    SIMPLE_SERIALIZE_MEMBERS(ProjectSpace)
}

#endif //CHRYSALIS_SPACE_H