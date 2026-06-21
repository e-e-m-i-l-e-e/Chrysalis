#include "PatternSpaceRendererData.h"

#include "ProjectSpace.h"

using namespace Chrysalis;

void PatternSpaceRendererData::pointAdded(const Point* point) {
    points_.emplace_back(*point);
    updateVBO();
}

void PatternSpaceRendererData::relativePointAdded(const Point* from, const Point* to) {
    static constexpr double ARROW_BASE_FACTOR = 0.75;
    static constexpr double ARROW_WING_LENGTH = 0.75;
    static constexpr double ARROW_WING_ANGLE = 20;

    pointAdded(to);
    auto intersection = ProjectSpace::xIntersection(*from, *to);
    if (!intersection) intersection = ProjectSpace::yIntersection(*from, *to);
    lines_.emplace_back(*from, static_cast<float>(ProjectSpace::length(*intersection, *from)));
    lines_.emplace_back(*to, static_cast<float>(ProjectSpace::length(*intersection, *to)));

    CGAL::Vector dir = *from - *to;
    dir /= std::sqrt(dir.squared_length());

    const CGAL::Vector shift = dir * POINT_RADIUS;

    dir *= ARROW_WING_LENGTH;

    arrows_.emplace_back(*to + ProjectSpace::rotate(dir + shift, ARROW_WING_ANGLE));
    arrows_.emplace_back(*to + shift);
    arrows_.emplace_back(*to + (dir + shift) * ARROW_BASE_FACTOR);
    arrows_.emplace_back(*to + ProjectSpace::rotate(dir + shift, -ARROW_WING_ANGLE));
}

bool PatternSpaceRendererData::isPointed(const float x, const float y) const {
    for (const auto& point: points_) {
        if (std::sqrt(std::pow(x - point.x(), 2) + std::pow(y - point.y(), 2)) <= POINT_RADIUS) return true;
    }
    return false;
}

size_t PatternSpaceRendererData::size() {
    return lines_.size() + arrows_.size() + points_.size();
}

std::vector<Vertex3f> PatternSpaceRendererData::vbo() {
    std::vector<Vertex3f> vbo = lines_;
    vbo.insert(vbo.end(), arrows_.begin(), arrows_.end());
    vbo.insert(vbo.end(), points_.begin(), points_.end());
    return vbo;
}

size_t PatternSpaceRendererData::linesSize() const {
    return lines_.size();
}

size_t PatternSpaceRendererData::arrowsSize() const {
    return arrows_.size();
}

size_t PatternSpaceRendererData::pointsSize() const {
    return points_.size();
}
