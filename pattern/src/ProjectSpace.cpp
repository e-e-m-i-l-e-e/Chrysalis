#include "ProjectSpace.h"

using namespace Chrysalis;

ProjectSpace::~ProjectSpace() {
    for (auto& point : points_) {
        delete point;
    }
}

void ProjectSpace::movePoint(const Point* point, const CG::Point position) const {
    if (const auto p = const_cast<Point*>(point); points_.contains(p)) p->move(position);
}

Point* ProjectSpace::addPoint(const double x, const double y) {
    return addPoint({x, y});
}

Point* ProjectSpace::addPoint(const CG::Point& point) {
    const auto p = new Point(point);
    points_.insert(p);
    return p;
}
