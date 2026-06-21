#ifndef CHRYSALIS_CONFIG_H
#define CHRYSALIS_CONFIG_H

#ifdef __CLANG_UML__
#include <CGAL/Simple_cartesian.h>
namespace CGAL {
    using Kernel = Simple_cartesian<double>;
}
#else
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
namespace CGAL {
    using Kernel = Exact_predicates_inexact_constructions_kernel;
}
#endif

namespace CGAL {
    static constexpr auto PRECISION = 15;
    using Line = Line_2<Kernel>;
    using Point = Point_2<Kernel>;
    using Vector = Vector_2<Kernel>;
}

#endif //CHRYSALIS_CONFIG_H