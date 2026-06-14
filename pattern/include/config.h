#ifndef CHRYSALIS_CONFIG_H
#define CHRYSALIS_CONFIG_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

namespace CGAL {
    static constexpr auto PRECISION = 15;

    using Kernel = Exact_predicates_inexact_constructions_kernel;

    using Line = Line_2<Kernel>;
    using Point = Point_2<Kernel>;
    using Vector = Vector_2<Kernel>;
}

#endif //CHRYSALIS_CONFIG_H