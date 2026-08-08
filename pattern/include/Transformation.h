#ifndef CHRYSALIS_TRANSFORMATION_H
#define CHRYSALIS_TRANSFORMATION_H

#include "CGAL.h"
#include "Point.h"

namespace Chrysalis {
    class Transformation {
    public:
        explicit Transformation() = default;
        explicit Transformation(const Point* origin, CG::Vector translation, double angle);

        CG::Point apply(CG::Point point) const;
    private:
        const Point* origin_ = nullptr;
        CG::Vector translation_ {0, 0};
        double angle_ = 0;
    };
}

#endif //CHRYSALIS_TRANSFORMATION_H
