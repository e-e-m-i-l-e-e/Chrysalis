#ifndef FASHIONDESIGNAPPS_SPACE_H
#define FASHIONDESIGNAPPS_SPACE_H

#include <unordered_map>

#include <CGAL/Simple_cartesian.h>

using Kernel = CGAL::Simple_cartesian<double>;
using Point = Kernel::Point_2;

class Space {
public:
    void addPoint(const std::string& name, double x, double y);
    Point& getPoint(const std::string& name);

    std::vector<float> getPoints() const;
private:
    std::unordered_map<std::string, Point> points_;
};

#endif //FASHIONDESIGNAPPS_SPACE_H