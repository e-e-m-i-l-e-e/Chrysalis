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

        void movePoint(const Point* point, CGAL::Point position) const;

        Point* addPoint(double x, double y);
        Point* addPoint(const CGAL::Point& point);

        static CGAL::Vector rotate(const CGAL::Vector& vector, double angle);
        static double angle(const CGAL::Vector& vector1, const CGAL::Vector& vector2);
        static double angle(const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
        static double length(const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
        static CGAL::Point relativePoint(const CGAL::Point& pointFrom, double angle, double length);
        static boost::optional<CGAL::Point> intersection(const CGAL::Line& line1, const CGAL::Line& line2);
        static boost::optional<CGAL::Point> xIntersection(const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
        static boost::optional<CGAL::Point> yIntersection(const CGAL::Point& pointFrom, const CGAL::Point& pointTo);
        static CGAL::Point circlesIntersection(const CGAL::Point& anchor, CGAL::CPoint center1, double radius1, CGAL::CPoint center2, double radius2);
    private:
        static double sin(double value);
        static double cos(double value);
        static double round(double value);
        /// @uml{composition[1:*]}
        std::unordered_set<Point*> points_;
    };
}

#endif //CHRYSALIS_SPACE_H