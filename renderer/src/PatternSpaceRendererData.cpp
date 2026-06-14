#include "PatternSpaceRendererData.h"

#include "ProjectSpace.h"

using namespace Chrysalis;

void PatternSpaceRendererData::pointAdded(const Point* point) {
    points_.emplace_back(*point);
    updateVBO();
}

void PatternSpaceRendererData::relativePointAdded(const Point* from, const Point* to) {
    pointAdded(to);
    auto intersection = ProjectSpace::xIntersection(*from, *to);
    if (!intersection) intersection = ProjectSpace::yIntersection(*from, *to);
    lines_.emplace_back(*from, static_cast<float>(ProjectSpace::length(*intersection, *from)));
    lines_.emplace_back(*to, static_cast<float>(ProjectSpace::length(*intersection, *to)));
}

size_t PatternSpaceRendererData::count() {
    return points_.size() + lines_.size();
}

std::vector<Vertex3f> PatternSpaceRendererData::vbo() {
    std::vector<Vertex3f> vbo = lines_;
    vbo.insert(vbo.end(), points_.begin(), points_.end());
    for (int i = 0; i < lines_.size(); i += 2)
    {
        std::cout << "(" << lines_[i].x() << ", " << lines_[i].y() << ")(" << lines_[i].attribute() << ") -> (" << lines_[i + 1].x() << ", " << lines_[i + 1].y() << ")(" << lines_[i + 1].attribute() << ")" << std::endl;
    }
    return vbo;
}

size_t PatternSpaceRendererData::pointsCount() const {
    return points_.size();
}

size_t PatternSpaceRendererData::linesCount() const {
    return lines_.size();
}
