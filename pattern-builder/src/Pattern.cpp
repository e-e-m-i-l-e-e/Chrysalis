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

void Pattern::addPoint(const std::string &from, const std::string &to, const Direction &direction, double distance) {
    addPoint(from, to, direction., distance);
}
