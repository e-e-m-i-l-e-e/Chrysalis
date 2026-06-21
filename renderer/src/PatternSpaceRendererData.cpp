#include "PatternSpaceRendererData.h"

#include "ProjectSpace.h"

using namespace Chrysalis;

PatternSpaceRendererData::Arrow PatternSpaceRendererData::buildArrow(const CGAL::Point& pointFrom, const CGAL::Point& pointTo) {
    static constexpr double ARROW_BASE_FACTOR = 0.75;
    static constexpr double ARROW_WING_LENGTH = 0.75;
    static constexpr double ARROW_WING_ANGLE = 20;

    CGAL::Vector dir = pointFrom - pointTo;
    dir /= std::sqrt(dir.squared_length());

    const CGAL::Vector shift = dir * POINT_RADIUS;

    dir *= ARROW_WING_LENGTH;
    return Arrow(
        pointTo + shift,
        pointTo + (dir + shift) * ARROW_BASE_FACTOR,
        pointTo + ProjectSpace::rotate(dir + shift, ARROW_WING_ANGLE),
        pointTo + ProjectSpace::rotate(dir + shift, -ARROW_WING_ANGLE)
    );
}

float PatternSpaceRendererData::length(const CGAL::Point& pointFrom, const CGAL::Point& pointTo) {
    return static_cast<float>(ProjectSpace::length(pointFrom, pointTo));
}

CGAL::Point PatternSpaceRendererData::intersectionPoint(const CGAL::Point& pointFrom, const CGAL::Point& pointTo) {
    auto intersection = ProjectSpace::xIntersection(pointFrom, pointTo);
    if (!intersection) intersection = ProjectSpace::yIntersection(pointFrom, pointTo);
    return intersection.value();
}

void PatternSpaceRendererData::pointMoved(const Point* point) {
    const auto positionLine = [&](const int pointIndex, const int existingPointIndex, const CGAL::Point& existingPoint) {
        const auto intersection = intersectionPoint(*point, existingPoint);
        lines_[pointIndex].move(*point);
        lines_[pointIndex].attribute(length(intersection, *point));
        lines_[existingPointIndex].attribute(length(intersection, existingPoint));
    };
    const auto positionArrow = [&](const int lineIndex, const CGAL::Point& pointFrom, const CGAL::Point& pointTo) {
        auto [baseBegin, baseEnd, leftWing, rightWing] = buildArrow(pointFrom, pointTo);
        arrows_[lineIndex * 2].move(leftWing);
        arrows_[lineIndex * 2 + 1].move(baseBegin);
        arrows_[lineIndex * 2 + 2].move(baseEnd);
        arrows_[lineIndex * 2 + 3].move(rightWing);
    };
    points_[pointIndices_[point]].move(*point);
    for (const auto& idx: linesFrom_[pointIndices_[point]]) {
        const auto toPoint = CGAL::Point(lines_[idx + 1].x(), lines_[idx + 1].y());
        positionLine(idx, idx + 1, toPoint);
        positionArrow(idx, *point, toPoint);
    }
    for (const auto& idx: linesTo_[pointIndices_[point]]) {
        const auto fromPoint = CGAL::Point(lines_[idx].x(), lines_[idx].y());
        positionLine(idx + 1, idx, fromPoint);
        positionArrow(idx, fromPoint, *point);
    }
    updateVBO();
}

void PatternSpaceRendererData::pointAdded(const Point* point) {
    observe(point);
    points_.emplace_back(*point);
    pointIndices_.emplace(point, points_.size() - 1);
    linesFrom_.emplace_back();
    linesTo_.emplace_back();
    updateVBO();
}

void PatternSpaceRendererData::relativePointAdded(const Point* from, const Point* to) {
    const auto intersection = intersectionPoint(*from, *to);
    lines_.emplace_back(*from, length(intersection, *from));
    lines_.emplace_back(*to, length(intersection, *to));
    linesFrom_[pointIndices_[from]].push_front(lines_.size() - 2);
    linesTo_[pointIndices_[to]].push_front(lines_.size() - 2);

    const auto [baseBegin, baseEnd, leftWing, rightWing] = buildArrow(*from, *to);

    arrows_.emplace_back(leftWing);
    arrows_.emplace_back(baseBegin);
    arrows_.emplace_back(baseEnd);
    arrows_.emplace_back(rightWing);

    updateVBO();
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
