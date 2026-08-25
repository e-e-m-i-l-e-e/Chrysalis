#include "PatternTraceRendererData.h"

#include <ranges>


using namespace Chrysalis;

PatternTraceRendererData::PatternTraceRendererData(BaseObservable<PatternTraceObserver>* observable,
                                                   const std::vector<BaseRendererObserver*>& observers)
    : BaseObservableRendererData(observers), observable_(observable) {
    observable_->addObserver(this);
}

PatternTraceRendererData::~PatternTraceRendererData() {
    observable_->removeObserver(this);
}

PatternTraceRendererData::Arrow PatternTraceRendererData::buildArrow(const CG::Point& pointFrom, const CG::Point& pointTo) {
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

float PatternTraceRendererData::length(const CG::Point& pointFrom, const CG::Point& pointTo) {
    return static_cast<float>(CG::length(pointFrom, pointTo));
}

CG::Point PatternTraceRendererData::intersectionPoint(const CG::Point& pointFrom, const CG::Point& pointTo) {
    auto intersection = CG::xIntersection(pointFrom, pointTo);
    if (!intersection) intersection = CG::yIntersection(pointFrom, pointTo);
    return intersection.value();
}

void PatternTraceRendererData::pointMoved(const Point* point) {
    const auto positionLine = [&](const int lineIndex, const bool editFrom, const CG::Point& existingPoint) {
        const auto intersection = intersectionPoint(*point, existingPoint);
        const int pointIndex = editFrom ? 0 : (lines_[lineIndex].size() - 1);
        const int existingPointIndex = editFrom ? (lines_[lineIndex].size() - 1) : 0;
        lines_[lineIndex][pointIndex].move(*point);
        lines_[lineIndex][pointIndex].attribute(length(intersection, *point));
        lines_[lineIndex][existingPointIndex].attribute(length(intersection, existingPoint));
    };
    const auto positionArrow = [&](const int lineIndex, const CG::Point& pointFrom, const CG::Point& pointTo) {
        auto [baseBegin, baseEnd, leftWing, rightWing] = buildArrow(pointFrom, pointTo);
        arrows_[lineIndex * 4].move(leftWing);
        arrows_[lineIndex * 4 + 1].move(baseBegin);
        arrows_[lineIndex * 4 + 2].move(baseEnd);
        arrows_[lineIndex * 4 + 3].move(rightWing);
    };
    points_[pointIndices_[point]].move(*point);
    for (const auto& [toPoint, idx]: connectionsMapFrom_[point]) {
        positionLine(idx, true, *toPoint);
        positionArrow(idx, *point, *toPoint);
    }
    for (const auto& [fromPoint, idx]: connectionsMapTo_[point]) {
        positionLine(idx, false, *fromPoint);
        positionArrow(idx, *fromPoint, *point);
    }
    updateVBO();
}

void PatternTraceRendererData::pointAdded(const Point* point) {
    observe(point);
    points_.emplace_back(*point);
    pointIndices_.emplace(point, points_.size() - 1);
    updateVBO();
}

void PatternTraceRendererData::curveAdded(const Curve* curve) {
    static constexpr double DISTANCE = 0.25;
    lines_.emplace_back();
    const auto curvePoints = curve->curvePoints(DISTANCE);
    for (int i = 0; i < curvePoints.size(); i++) {
        lines_.back().emplace_back(curvePoints[i], 0);
    }
    updateVBO();
}

void PatternTraceRendererData::transformed(const Transformation& transformation) {
    for (auto& point: points_) {
        point.transform(transformation);
    }
    for (auto& line: lines_) {
        for (auto& point: line) {
            point.transform(transformation);
        }
    }
    for (auto& point: arrows_) {
        point.transform(transformation);
    }
    updateVBO();
}

void PatternTraceRendererData::relativePointConnectionAdded(const Point* from, const Point* to) {
    const auto intersection = intersectionPoint(*from, *to);
    lines_.emplace_back();
    lines_.back().emplace_back(*from, length(intersection, *from));
    lines_.back().emplace_back(*to, length(intersection, *to));
    connectionsMapFrom_[from][to] = lines_.size() - 1;
    connectionsMapTo_[to][from] = lines_.size() - 1;

    const auto [baseBegin, baseEnd, leftWing, rightWing] = buildArrow(*from, *to);

    arrows_.emplace_back(leftWing);
    arrows_.emplace_back(baseBegin);
    arrows_.emplace_back(baseEnd);
    arrows_.emplace_back(rightWing);

    updateVBO();
}

void PatternTraceRendererData::relativePointConnectionRemoved(const Point* from, const Point* to) {
    if (connectionsMapFrom_[from].contains(to)) {
        const int lineToRemove = connectionsMapFrom_[from][to];
        const auto shiftIndicesInMap = [&lineToRemove](std::unordered_map<const Point*, std::unordered_map<const Point*, int>>& connections,
                                          const Point* first, const Point* second) {
            connections[first].erase(second);
            for (auto& points: connections | std::ranges::views::values) {
                for (auto& index: points | std::ranges::views::values) {
                    if (index > lineToRemove) index--;
                }
            }
        };
        lines_.erase(lines_.begin() + lineToRemove);
        const auto it = arrows_.begin() + lineToRemove * 4;
        arrows_.erase(it, it + 4);
        shiftIndicesInMap(connectionsMapFrom_, from, to);
        shiftIndicesInMap(connectionsMapTo_, to, from);
    }
    updateVBO();
}

const Point* PatternTraceRendererData::pointAtPosition(const float x, const float y) const {
    for (const auto& point : pointIndices_ | std::views::keys) {
        if (std::sqrt(std::pow(x - point->x(), 2) + std::pow(y - point->y(), 2)) <= POINT_RADIUS) return point;
    }
    return nullptr;
}

size_t PatternTraceRendererData::size() {
    return arrows_.size() + points_.size() +
           std::accumulate(lines_.begin(), lines_.end(), 0,
                           [](size_t sum, const auto& line) {
                               return sum + line.size();
           });
}

std::vector<Vertex3f> PatternTraceRendererData::vbo() {
    std::vector<Vertex3f> vbo;
    vbo.insert(vbo.end(), points_.begin(), points_.end());
    vbo.insert(vbo.end(), arrows_.begin(), arrows_.end());
    for (const auto& line: lines_) {
        vbo.insert(vbo.end(), line.begin(), line.end());
    }
    return vbo;
}

Layout PatternTraceRendererData::pointsLayout() const {
    return Layout(0, points_.size());
}

std::vector<Layout> PatternTraceRendererData::linesLayout() const {
    size_t offset = points_.size() + arrows_.size();
    std::vector<Layout> layout {};
    layout.reserve(lines_.size());
    for (const auto& line: lines_) {
        layout.emplace_back(offset, line.size());
        offset += line.size();
    }
    return layout;
}

std::vector<Layout> PatternTraceRendererData::arrowsLayout() const {
    size_t offset = points_.size();
    std::vector<Layout> layout {};
    layout.reserve(arrows_.size() / 4);
    for (int i = 0; i < arrows_.size(); i += 4) {
        layout.emplace_back(offset, 4);
        offset += 4;
    }
    return layout;
}
