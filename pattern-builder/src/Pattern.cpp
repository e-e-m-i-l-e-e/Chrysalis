#include "Pattern.h"

Pattern::Pattern(const std::string &name): name_(name) {}

void Pattern::addPoint(const std::string& name, double x, double y) {
    // TODO: what to do when point with this name / coordinates already exists?
    points_[name] = Point(x, y);
}

void Pattern::addPoint(const std::string &from, const std::string &to, double radians, double distance) {
    if (!points_.contains(from)) {
        // TODO: ?
        return;
    }
    points_[to] = points_[from] + Vector(std::cos(radians), std::sin(radians)) * distance;
}

void Pattern::test() {
    // Outer boundary (must be counter-clockwise)
    Polygon outer;
    outer.push_back(Point(0, 0));
    outer.push_back(Point(10, 0));
    outer.push_back(Point(10, 10));
    outer.push_back(Point(0, 10));

    // Hole (must be clockwise — opposite of outer)
    Polygon hole;
    hole.push_back(Point(2, 2));
    hole.push_back(Point(2, 50));
    hole.push_back(Point(50, 50));
    hole.push_back(Point(50, 2));

    // Construct the polygon with holes
    Polygon_with_holes pwh(outer);
    pwh.add_hole(hole);
}
