#include "Space.h"

#include <ranges>

void Space::addPoint(const std::string& name, double x, double y) {
    points_[name] = Point(x, y);
}

Point& Space::getPoint(const std::string& name) {
    return points_[name];
}

std::vector<float> Space::getPoints() const {
    int i = 0;
    auto points = std::vector<float>(points_.size() * 2);
    for (const auto& point: points_ | std::views::values) {
        points[i] = point.x();
        points[i + 1] = point.y();
        i += 2;
    }
    return points;
}
