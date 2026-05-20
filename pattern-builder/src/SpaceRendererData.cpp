#include "SpaceRendererData.h"

#include <numbers>

std::vector<SpaceVertex> SpaceRendererData::getVBO() const {
    std::vector<SpaceVertex> vbo;
    vbo.insert(vbo.end(), points_.begin(), points_.end());
    vbo.insert(vbo.end(), lines_.begin(), lines_.end());
    vbo.insert(vbo.end(), arrows_.begin(), arrows_.end());
    return vbo;
}

int SpaceRendererData::size() const {
    return sizeof(SpaceVertex) * (points_.size() + lines_.size() + arrows_.size());
}

SpaceRendererData::Range SpaceRendererData::linesRange() const {
    return pointsRange() + lines_;
}

SpaceRendererData::Range SpaceRendererData::pointsRange() const {
    return {0, points_.size()};
}

SpaceRendererData::Range SpaceRendererData::arrowsRange() const {
    return linesRange() + arrows_;
}

void SpaceRendererData::addPoint(const Point& point) {
    points_.emplace_back(point.x(), point.y(), 0);
}

void SpaceRendererData::addArrow(const Point& from, const Point& to) {
    Vector dir(from.x() - to.x(), from.y() - to.y());
    const double len = std::sqrt(CGAL::to_double(dir.squared_length()));

    constexpr double arrowLength = 1; // world-space size, tweak to taste
    dir = dir * (arrowLength / len);

    constexpr double angle = std::numbers::pi / 8.0; // 30 degrees
    const CGAL::Aff_transformation_2<Kernel> rotPos(CGAL::ROTATION, std::sin(angle),  std::cos(angle));
    const CGAL::Aff_transformation_2<Kernel> rotNeg(CGAL::ROTATION, std::sin(-angle), std::cos(-angle));

    const Vector wing1 = rotPos(dir);
    const Vector wing2 = rotNeg(dir);
    const Vector base  = dir * 0.75;

    arrows_.emplace_back(static_cast<float>(to.x() + wing1.x()), static_cast<float>(to.y() + wing1.y()), 0.f);
    arrows_.emplace_back(static_cast<float>(to.x()),              static_cast<float>(to.y()),              0.f);
    arrows_.emplace_back(static_cast<float>(to.x() + base.x()),  static_cast<float>(to.y() + base.y()),  0.f);
    arrows_.emplace_back(static_cast<float>(to.x() + wing2.x()), static_cast<float>(to.y() + wing2.y()), 0.f);
}

void SpaceRendererData::addLine(const Point& from, const Point& to, const double distance) {
    lines_.emplace_back(from.x(), from.y(), 0);
    lines_.emplace_back(to.x(), to.y(), distance);
    addArrow(from, to);
}
