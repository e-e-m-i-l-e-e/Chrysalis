#ifndef FASHIONDESIGNAPPS_SPACERENDERERDATA_H
#define FASHIONDESIGNAPPS_SPACERENDERERDATA_H

#include <vector>

#include <CGAL/Simple_cartesian.h>

#include "SpaceVertex.h"

using Kernel = CGAL::Simple_cartesian<double>;
using Point = Kernel::Point_2;
using Vector = Kernel::Vector_2;

class SpaceRendererData {
    friend class Space;
public:
    struct Range {
        size_t from;
        size_t count;

        Range operator+(const std::vector<SpaceVertex>& vertices) const {
            return {from + count, vertices.size()};
        }
    };
    std::vector<SpaceVertex> getVBO() const;

    Range pointsRange() const;
    Range arrowsRange() const;
    std::vector<Range> linesRanges() const;
private:
    void addPoint(const Point& point);
    void addArrow(const Point& from, const Point& to);

    int addLine(const Point& from, const Point& to, double distance);
    void extendLine(int lineIndex, const Point& point, double distance);

    std::vector<SpaceVertex> points_;
    std::vector<SpaceVertex> arrows_;
    std::vector<std::vector<SpaceVertex>> lines_;
};

#endif //FASHIONDESIGNAPPS_SPACERENDERERDATA_H