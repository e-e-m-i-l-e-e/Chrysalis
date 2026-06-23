#ifndef CHRYSALIS_CGAL_STUBS_H
#define CHRYSALIS_CGAL_STUBS_H

#include <utility>
#include <variant>

namespace CGAL {
    template <typename From, typename To>
    class Cartesian_converter {
    public:
        typename To::Point_2 operator()(const typename From::Point_2& p) {
            return typename To::Point_2();
        }
    };

    template <typename K>
    class Circular_arc_point_2 {
    public:
        double x() const { return 0.0; }
        double y() const { return 0.0; }
    };

    template <typename K, typename C1, typename C2>
    struct CK2_Intersection_traits {
        using type = std::variant<
            std::pair<Circular_arc_point_2<K>, unsigned int>,
            C1
        >;
    };

    template <typename C1, typename C2, typename OutputIterator>
    OutputIterator intersection(const C1&, const C2&, OutputIterator out) {
        return out;
    }

}
#endif //CHRYSALIS_CGAL_STUBS_H