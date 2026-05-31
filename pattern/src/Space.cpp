#include "Space.h"

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
    std::cout << fromPointName << " " << name << " " << angle << " " << length << std::endl;
    const auto& fromPoint = points_[fromPointName];
    const auto& toPoint = Point(fromPoint.x() + length * std::cos(angle * CGAL_PI / 180.0), fromPoint.y() + length * std::sin(angle * CGAL_PI / 180.0));
    addPoint(name, toPoint);

    if (parentPoints_.contains(fromPointName) && linesIndices_.contains(fromPointName)) {
        rendererData_->extendLine(linesIndices_[fromPointName], toPoint, length);
        linesIndices_[name] = linesIndices_[fromPointName];
        linesIndices_.erase(fromPointName);
    } else {
        linesIndices_[name] = rendererData_->addLine(fromPoint, toPoint, length);
    }
    parentPoints_[name] = fromPointName;
}

void Space::addPoint(const std::string& fromPointName, const std::string& name, const Direction direction, const double length) {
    static std::unordered_map<Direction, double> directions = {
        {RIGHT, 0},
        {LEFT, 180},
        {UP, 90},
        {DOWN, 270}
    };
    addPoint(fromPointName, name, directions[direction], length);
}

void Space::nextPoint(const std::string& name, const double angle, const double length) {
    addPoint(std::string(lastPointName_), name, angle, length);
}

void Space::nextPoint(const std::string& name, const Direction direction, const double length) {
    addPoint(std::string(lastPointName_), name, direction, length);
}

double Space::angle(const std::string& from, const std::string& to) const {
    const Vector vector = points_.at(to) - points_.at(from);
    return std::atan2(CGAL::to_double(vector.y()), CGAL::to_double(vector.x())) * 180.0 / CGAL_PI;
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