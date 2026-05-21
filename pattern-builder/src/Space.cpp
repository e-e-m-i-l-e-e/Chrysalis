#include "Space.h"

#include <numbers>

Space::Space(SpaceRendererData* rendererData): rendererData_(rendererData) {}

Space::~Space() {
    delete rendererData_;
}

void Space::addPoint(const std::string& name, const Point& point) {
    points_[name] = point;
    lastPointName_ = name;
    rendererData_->addPoint(point);
}

void Space::addPoint(const std::string& name, double x, double y) {
    addPoint(name, Point(x, y));
}

void Space::addPoint(const std::string& fromPointName, const std::string& name, const double angle, const double length) {
    const auto& fromPoint = points_[fromPointName];
    const auto& toPoint = Point(fromPoint.x() + length * std::cos(angle), fromPoint.y() + length * std::sin(angle));
    addPoint(name, toPoint);

    if (parentPoints_.contains(fromPointName) && tailPoints_.contains(fromPointName)) {
        std::string rootPointName = fromPointName;
        while (parentPoints_.contains(rootPointName)) {
            rootPointName = parentPoints_[rootPointName];
        }
        rendererData_->extendLine(linesIndices_[rootPointName], toPoint, length);
    } else {
        linesIndices_[fromPointName] = rendererData_->addLine(fromPoint, toPoint, length);
    }
    parentPoints_[name] = fromPointName;
    tailPoints_.erase(fromPointName);
    tailPoints_.insert(name);
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
    addPoint(std::string(lastPointName_), name, angle, length);
}

void Space::nextPoint(const std::string& name, const Direction direction, const double length) {
    addPoint(std::string(lastPointName_), name, direction, length);
}

double Space::distance(const std::string& from, const std::string& to) const {
    return std::sqrt(CGAL::to_double(CGAL::squared_distance(points_.at(from), points_.at(to))));
}

Point& Space::getPoint(const std::string& name) {
    return points_[name];
}

const SpaceRendererData* Space::getRendererData() const {
    return rendererData_;
}