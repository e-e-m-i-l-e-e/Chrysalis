#ifndef FASHIONDESIGNAPPS_PATTERN_H
#define FASHIONDESIGNAPPS_PATTERN_H

#include <unordered_map>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_with_holes_2.h>

class Pattern {
    using Kernel = CGAL::Simple_cartesian<double>;
    using Point = Kernel::Point_2;
    using Vector = Kernel::Vector_2;
    using Polygon = CGAL::Polygon_2<Kernel>;
    using Polygon_with_holes = CGAL::Polygon_with_holes_2<Kernel>;
public:
    explicit Pattern(const std::string& name);

    void addPoint(const std::string& name, double x, double y);
    void addPoint(const std::string& from, const std::string& to, double radians, double distance);

    void test();
private:
    std::string name_;
    std::unordered_map<std::string, Point> points_;
};

#endif //FASHIONDESIGNAPPS_PATTERN_H