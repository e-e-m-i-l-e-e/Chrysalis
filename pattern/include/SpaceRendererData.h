#ifndef CHRYSALIS_SPACERENDERERDATA_H
#define CHRYSALIS_SPACERENDERERDATA_H

#include <vector>

#include <CGAL/Simple_cartesian.h>

#include "serialization.h"
#include "SpaceVertex.h"

using Kernel = CGAL::Simple_cartesian<double>;
using Point = Kernel::Point_2;
using Vector = Kernel::Vector_2;

namespace Chrysalis {
    class SERIALIZABLE(SpaceRendererData) {
        friend class ProjectSpace;
    public:
        explicit SpaceRendererData();
        ~SpaceRendererData();

        struct Range {
            size_t from;
            size_t count;

            Range operator+(const std::vector<SpaceVertex>& vertices) const {
                return {from + count, vertices.size()};
            }
        };
        std::vector<SpaceVertex> getVBO() const;
        std::vector<SpaceVertex> getPoints() const;

        Range pointsRange() const;
        std::vector<Range> linesRanges() const;
        std::vector<Range> arrowsRanges() const;
    private:
        void addPoint(const Point& point) const;
        int addLine(const Point& from, const Point& to, double distance) const;
        void extendLine(int lineIndex, const Point& point, double distance) const;

        struct Private;
        Private* p;
    };
    DEFAULT_SERIALIZE_MEMBERS(SpaceRendererData)
}

#endif //CHRYSALIS_SPACERENDERERDATA_H