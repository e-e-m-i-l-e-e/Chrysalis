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
        Point* addPoint(const CGAL::Point& pointFrom, double angle, double length);

        static CGAL::Vector rotate(const CGAL::Vector& vector, double angle);
        static double angle(const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
        static double length(const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
        static boost::optional<CGAL::Point> xIntersection(const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
        static boost::optional<CGAL::Point> yIntersection(const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
    private:
        static double sin(double value);
        static double cos(double value);
        static double round(double value);
        static boost::optional<CGAL::Point> intersection(const CGAL::Line& line, const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
        /// @uml{composition[1:*]}
        std::unordered_set<Point*> points_;
    };
    SIMPLE_SERIALIZE_MEMBERS(ProjectSpace)
}

#endif //CHRYSALIS_SPACE_H