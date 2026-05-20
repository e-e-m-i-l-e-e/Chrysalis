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

    int size() const;
    Range linesRange() const;
    Range pointsRange() const;
    Range arrowsRange() const;
private:
    void addPoint(const Point& point);
    void addArrow(const Point& from, const Point& to);
    void addLine(const Point& from, const Point& to, double distance);

    std::vector<SpaceVertex> lines_;
    std::vector<SpaceVertex> points_;
    std::vector<SpaceVertex> arrows_;
};

#endif //FASHIONDESIGNAPPS_SPACERENDERERDATA_H