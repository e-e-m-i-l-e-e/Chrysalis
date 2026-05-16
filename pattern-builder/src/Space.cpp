#include "Space.h"

#include <ranges>
#include <numbers>

void Space::addPoint(const std::string& name, double x, double y) {
    points_[name] = Point(x, y);
    insertionOrder_.push_back(name);
    vboPoints_.emplace_back(static_cast<float>(x), static_cast<float>(y));
}

void Space::addPoint(const std::string& fromPointName, const std::string& name, const double angle, const double length) {
    const auto& fromPoint = points_[fromPointName];
    addPoint(name, fromPoint.x() + length * std::cos(angle), fromPoint.y() + length * std::sin(angle));
    parentPoints_[name] = fromPointName;
}

void Space::addPoint(const std::string& fromPointName, const std::string& name, const Direction direction, const double length) {
    static std::unordered_map<Direction, double> directions = {
        {RIGHT, 0 * std::numbers::pi / 180},
        {LEFT, 180 * std::numbers::pi / 180},
        {UP, 90 * std::numbers::pi / 180},
        {DOWN, 270 * std::numbers::pi / 180}
    };
    addPoint(fromPointName, name, directions[direction], length);
}

void Space::nextPoint(const std::string& name, const double angle, const double length) {
    addPoint(insertionOrder_.back(), name, angle, length);
}

void Space::nextPoint(const std::string& name, const Direction direction, const double length) {
    addPoint(insertionOrder_.back(), name, direction, length);
}

double Space::distance(const std::string& from, const std::string& to) const {
    return std::sqrt(CGAL::to_double(CGAL::squared_distance(points_.at(from), points_.at(to))));
}

Point& Space::getPoint(const std::string& name) {
    return points_[name];
}

std::vector<Vertex> Space::getVBO() const {
    return vboPoints_;
}

std::vector<DistancedVertex> Space::getDistancedVBO() const {
    std::vector<DistancedVertex> distancedVBO;
    std::unordered_map<std::string, double> distances;
    for (const auto& name: insertionOrder_) {
        if (parentPoints_.contains(name)) {
            distances[name] = distances[parentPoints_.at(name)] + distance(name, parentPoints_.at(name));
        } else {
            distances[name] = 0;
        }
        const auto point = points_.at(name);
        distancedVBO.emplace_back(
            static_cast<float>(point.x()),
            static_cast<float>(point.y()),
            static_cast<float>(distances[name])
        );
    }
    for (const auto& [name, dist]: distances) {
        std::cout << name << ": " << dist << std::endl;
    }
    return distancedVBO;
}
