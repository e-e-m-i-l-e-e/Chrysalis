#ifndef FASHIONDESIGNAPPS_PATTERN_H
#define FASHIONDESIGNAPPS_PATTERN_H

#include <unordered_map>

#include <CGAL/Simple_cartesian.h>

class Pattern {
    using Kernel = CGAL::Simple_cartesian<double>;
    using Point = Kernel::Point_2;
    using Vector = Kernel::Vector_2;
public:
    explicit Pattern(const std::string& name);

    void addPoint(const std::string& name, double x, double y);
    void addPoint(const std::string& from, const std::string& to, double radians, double distance);
    void addPoint(const std::string& from, const std::string& to, const Direction& direction, double distance);
private:
    std::string name_;
    std::unordered_map<std::string, Point> points_;
};

#endif //FASHIONDESIGNAPPS_PATTERN_H