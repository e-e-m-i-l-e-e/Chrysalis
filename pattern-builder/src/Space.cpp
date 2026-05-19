#include "Space.h"

#include <ranges>
#include <numbers>

Space::Space(const SpaceRendererData* rendererData): rendererData_(rendererData) {}

Space::~Space() {
    delete rendererData_;
}

void Space::addPoint(const std::string& name, double x, double y) {
    points_[name] = Point(x, y);
    insertionOrder_.push_back(name);
    // vboPoints_.emplace_back(static_cast<float>(x), static_cast<float>(y));
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

std::vector<SpaceVertex> Space::getVBO() const {
    std::vector<SpaceVertex> vbo;
    std::vector<SpaceVertex> arrows;
    for (const auto& point : points_ | std::views::values) {
        vbo.emplace_back(point.x(), point.y(), 0);
    }
    for (const auto& name: insertionOrder_) {
        if (parentPoints_.contains(name)) {
            auto point = points_.at(name);
            vbo.emplace_back(
                static_cast<float>(point.x()),
                static_cast<float>(point.y()),
                static_cast<float>(0)
            );
            point = points_.at(parentPoints_.at(name));
            vbo.emplace_back(
                static_cast<float>(point.x()),
                static_cast<float>(point.y()),
                static_cast<float>(distance(name, parentPoints_.at(name)))
            );

            auto& from = points_.at(name);
            auto& to = points_.at(parentPoints_.at(name));

            // Arrowhead — direction from 'to' back toward 'from', normalized
            Vector dir(from.x() - to.x(), from.y() - to.y());
            const double len = std::sqrt(CGAL::to_double(dir.squared_length()));
            if (len < 1e-10) continue;

            const double arrowLength = 1; // world-space size, tweak to taste
            dir = dir * (arrowLength / len);

            const double angle = std::numbers::pi / 8.0; // 30 degrees
            const CGAL::Aff_transformation_2<Kernel> rotPos(CGAL::ROTATION, std::sin(angle),  std::cos(angle));
            const CGAL::Aff_transformation_2<Kernel> rotNeg(CGAL::ROTATION, std::sin(-angle), std::cos(-angle));

            const Vector wing1 = rotPos(dir);
            const Vector wing2 = rotNeg(dir);
            const Vector base  = dir;

            arrows.emplace_back(static_cast<float>(to.x() + wing1.x()), static_cast<float>(to.y() + wing1.y()), 0.f);
            arrows.emplace_back(static_cast<float>(to.x()),              static_cast<float>(to.y()),              0.f);
            arrows.emplace_back(static_cast<float>(to.x() + base.x()),  static_cast<float>(to.y() + base.y()),  0.f);
            arrows.emplace_back(static_cast<float>(to.x() + wing2.x()), static_cast<float>(to.y() + wing2.y()), 0.f);

            // Wing 1: tip -> tip + wing1
            // arrows.emplace_back(static_cast<float>(to.x()),              static_cast<float>(to.y()),              0.f);
            // arrows.emplace_back(static_cast<float>(to.x() + wing1.x()), static_cast<float>(to.y() + wing1.y()), 0.f);

            // Wing 2: tip -> tip + wing2
            // arrows.emplace_back(static_cast<float>(to.x()),              static_cast<float>(to.y()),              0.f);
            // arrows.emplace_back(static_cast<float>(to.x() + wing2.x()), static_cast<float>(to.y() + wing2.y()), 0.f);
        }
    }
    std::cout << arrows.size() << std::endl;
    vbo.insert(vbo.end(), arrows.begin(), arrows.end());
    return vbo;
}

int Space::getNumberOfPoints() const {
    return points_.size();
}

// std::vector<DistancedVertex> Space::getDistancedVBO() const {
//     std::vector<DistancedVertex> distancedVBO;
//     std::unordered_map<std::string, double> distances;
//     for (const auto& name: insertionOrder_) {
//         if (parentPoints_.contains(name)) {
//             distances[name] = distances[parentPoints_.at(name)] + distance(name, parentPoints_.at(name));
//         } else {
//             distances[name] = 0;
//         }
//         const auto point = points_.at(name);
//         distancedVBO.emplace_back(
//             static_cast<float>(point.x()),
//             static_cast<float>(point.y()),
//             static_cast<float>(distances[name])
//         );
//     }
//     for (const auto& [name, dist]: distances) {
//         std::cout << name << ": " << dist << std::endl;
//     }
//     return distancedVBO;
// }
