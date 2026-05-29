#ifndef CHRYSALIS_DART_H
#define CHRYSALIS_DART_H

#include <CGAL/Polygon_2.h>
#include <CGAL/Simple_cartesian.h>

#include "Space.h"

namespace Chrysalis {
    using Polygon = CGAL::Polygon_2<Kernel>;

    class Dart {
    public:
        explicit Dart(Space* space);

        void addPoint(const std::string& pointName);
        Polygon& getPolygon();

        std::vector<float> getPoints();
    private:
        Space* space_;
        Polygon polygon_;
    };
}

#endif //CHRYSALIS_DART_H