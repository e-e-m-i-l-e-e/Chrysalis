#include "SpaceRendererData.h"

#include <numbers>

using namespace Chrysalis;

struct SpaceRendererData::Private {
    void addArrow(const Point& from, const Point& to);

    std::vector<SpaceVertex> points_;
    std::vector<std::vector<SpaceVertex>> arrows_;
    std::vector<std::vector<SpaceVertex>> lines_;
};

SpaceRendererData::SpaceRendererData(): p(new Private()) {}

SpaceRendererData::~SpaceRendererData() {
    delete p;
}

std::vector<SpaceVertex> SpaceRendererData::getVBO() const {
    std::vector<SpaceVertex> vbo;
    vbo.insert(vbo.end(), p->points_.begin(), p->points_.end());
    for (const auto& line: p->lines_) {
        vbo.insert(vbo.end(), line.begin(), line.end());
    }
    for (const auto& arrow: p->arrows_) {
        vbo.insert(vbo.end(), arrow.begin(), arrow.end());
    }
    return vbo;
}

std::vector<SpaceVertex> SpaceRendererData::getPoints() const {
    return p->points_;
}

SpaceRendererData::Range SpaceRendererData::pointsRange() const {
    return {0, p->points_.size()};
}

std::vector<SpaceRendererData::Range> SpaceRendererData::linesRanges() const {
    auto [pointsFrom, pointsCount] = pointsRange();
    size_t from = pointsFrom + pointsCount;
    std::vector<Range> ranges(p->lines_.size());
    for (int i = 0; i < p->lines_.size(); i++) {
        ranges[i] = {from, p->lines_[i].size()};
        from += p->lines_[i].size();
    }
    return ranges;
}

std::vector<SpaceRendererData::Range> SpaceRendererData::arrowsRanges() const {
    if (p->lines_.empty()) return {};
    auto [lastLineFrom, lastLineCount] = linesRanges()[p->lines_.size() - 1];
    size_t from = lastLineFrom + lastLineCount;
    std::vector<Range> ranges(p->arrows_.size());
    for (int i = 0; i < p->arrows_.size(); i++) {
        ranges[i] = {from, p->arrows_[i].size()};
        from += p->arrows_[i].size();
    }
    return ranges;
}

void SpaceRendererData::addPoint(const Point& point) const {
    p->points_.emplace_back(point.x(), point.y(), 0);
}

void SpaceRendererData::Private::addArrow(const Point& from, const Point& to) {
    constexpr double arrowLength = 1;
    constexpr double baseFactor = 0.75;
    constexpr double angle = std::numbers::pi / 8.0;

    Vector dir(from.x() - to.x(), from.y() - to.y());
    dir *= arrowLength / std::sqrt(CGAL::to_double(dir.squared_length()));

    const Vector wingPositive = CGAL::Aff_transformation_2<Kernel>(CGAL::ROTATION, std::sin(angle), std::cos(angle))(dir);
    const Vector wingNegative = CGAL::Aff_transformation_2<Kernel>(CGAL::ROTATION, std::sin(-angle), std::cos(-angle))(dir);
    const Vector base  = dir * baseFactor;

    arrows_.emplace_back(std::vector{
        SpaceVertex(to.x() + wingPositive.x(), to.y() + wingPositive.y(), 0.f),
        SpaceVertex(to.x(), to.y(), 0.f),
        SpaceVertex(to.x() + base.x(), to.y() + base.y(), 0.f),
        SpaceVertex(to.x() + wingNegative.x(), to.y() + wingNegative.y(), 0.f)
    });
}

int SpaceRendererData::addLine(const Point& from, const Point& to, const double distance) const
{
    std::vector<SpaceVertex> line;
    line.emplace_back(from.x(), from.y(), 0);
    line.emplace_back(to.x(), to.y(), distance);
    p->lines_.push_back(line);
    p->addArrow(from, to);
    return p->lines_.size() - 1;
}

void SpaceRendererData::extendLine(const int lineIndex, const Point& point, const double distance) const {
    const SpaceVertex from = p->lines_[lineIndex].back();
    p->lines_[lineIndex].emplace_back(point.x(), point.y(), distance + p->lines_[lineIndex].back().distance());
    p->addArrow({from.x(), from.y()}, point);
}
