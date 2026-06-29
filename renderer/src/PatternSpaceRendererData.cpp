#include "PatternSpaceRendererData.h"

#include <ranges>

#include "ProjectSpace.h"

using namespace Chrysalis;

PatternSpaceRendererData::Arrow PatternSpaceRendererData::buildArrow(const CG::Point& pointFrom, const CG::Point& pointTo) {
    static constexpr double ARROW_BASE_FACTOR = 0.75;
    static constexpr double ARROW_WING_LENGTH = 0.75;
    static constexpr double ARROW_WING_ANGLE = 20;

    CG::Vector dir = pointFrom - pointTo;
    dir /= std::sqrt(dir.squared_length());

    const CG::Vector shift = dir * POINT_RADIUS;

    dir *= ARROW_WING_LENGTH;
    return Arrow(
        pointTo + shift,
        pointTo + (dir + shift) * ARROW_BASE_FACTOR,
        pointTo + CG::rotate(dir + shift, ARROW_WING_ANGLE),
        pointTo + CG::rotate(dir + shift, -ARROW_WING_ANGLE)
    );
}

float PatternSpaceRendererData::length(const CG::Point& pointFrom, const CG::Point& pointTo) {
    return static_cast<float>(CG::length(pointFrom, pointTo));
}

CG::Point PatternSpaceRendererData::intersectionPoint(const CG::Point& pointFrom, const CG::Point& pointTo) {
    auto intersection = CG::xIntersection(pointFrom, pointTo);
    if (!intersection) intersection = CG::yIntersection(pointFrom, pointTo);
    return intersection.value();
}

void PatternSpaceRendererData::pointMoved(const Point* point) {
    const auto positionLine = [&](const int pointIndex, const int existingPointIndex, const CG::Point& existingPoint) {
        const auto intersection = intersectionPoint(*point, existingPoint);
        lines_[pointIndex].move(*point);
        lines_[pointIndex].attribute(length(intersection, *point));
        lines_[existingPointIndex].attribute(length(intersection, existingPoint));
    };
    const auto positionArrow = [&](const int lineIndex, const CG::Point& pointFrom, const CG::Point& pointTo) {
        auto [baseBegin, baseEnd, leftWing, rightWing] = buildArrow(pointFrom, pointTo);
        arrows_[lineIndex * 2].move(leftWing);
        arrows_[lineIndex * 2 + 1].move(baseBegin);
        arrows_[lineIndex * 2 + 2].move(baseEnd);
        arrows_[lineIndex * 2 + 3].move(rightWing);
    };
    points_[pointIndices_[point]].move(*point);
    for (const auto& [toPoint, idx]: connectionsMapFrom_[point]) {
        positionLine(idx, idx + 1, *toPoint);
        positionArrow(idx, *point, *toPoint);
    }
    for (const auto& [fromPoint, idx]: connectionsMapTo_[point]) {
        positionLine(idx + 1, idx, *fromPoint);
        positionArrow(idx, *fromPoint, *point);
    }
    updateVBO();
}

void PatternSpaceRendererData::pointAdded(const Point* point) {
    observe(point);
    points_.emplace_back(*point);
    pointIndices_.emplace(point, points_.size() - 1);
    updateVBO();
}

void PatternSpaceRendererData::relativePointConnectionAdded(const Point* from, const Point* to) {
    const auto intersection = intersectionPoint(*from, *to);
    lines_.emplace_back(*from, length(intersection, *from));
    lines_.emplace_back(*to, length(intersection, *to));
    connectionsMapFrom_[from][to] = lines_.size() - 2;
    connectionsMapTo_[to][from] = lines_.size() - 2;

    const auto [baseBegin, baseEnd, leftWing, rightWing] = buildArrow(*from, *to);

    arrows_.emplace_back(leftWing);
    arrows_.emplace_back(baseBegin);
    arrows_.emplace_back(baseEnd);
    arrows_.emplace_back(rightWing);

    updateVBO();
}

void PatternSpaceRendererData::relativePointConnectionRemoved(const Point* from, const Point* to) {
    if (connectionsMapFrom_[from].contains(to)) {
        const int lineToRemove = connectionsMapFrom_[from][to];
        const auto shiftIndicesInMap = [&lineToRemove](std::unordered_map<const Point*, std::unordered_map<const Point*, int>>& connections,
                                          const Point* first, const Point* second) {
            connections[first].erase(second);
            for (auto& points: connections | std::ranges::views::values) {
                for (auto& index: points | std::ranges::views::values) {
                    if (index > lineToRemove) index -= 2;
                }
            }
        };
        lines_.erase(lines_.begin() + lineToRemove, lines_.begin() + (lineToRemove + 2));
        arrows_.erase(arrows_.begin() + lineToRemove * 2, arrows_.begin() + lineToRemove * 2 + 4);
        shiftIndicesInMap(connectionsMapFrom_, from, to);
        shiftIndicesInMap(connectionsMapTo_, to, from);
    }
    updateVBO();
}

const Point* PatternSpaceRendererData::pointAtPosition(const float x, const float y) const {
    for (const auto& point : pointIndices_ | std::views::keys) {
        if (std::sqrt(std::pow(x - point->x(), 2) + std::pow(y - point->y(), 2)) <= POINT_RADIUS) return point;
    }
    return nullptr;
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
