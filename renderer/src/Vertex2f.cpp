#include "Vertex2f.h"

using namespace Chrysalis;

Vertex2f::Vertex2f(const float x, const float y): x_(x), y_(y) {}

Vertex2f::Vertex2f(const Point& point): x_(point.x()), y_(point.y()) {}

const float& Vertex2f::x() const {
    return x_;
}

const float& Vertex2f::y() const {
    return y_;
}

void Vertex2f::move(const Point& point) {
    x_ = point.x();
    y_ = point.y();
}

void Vertex2f::transform(const Transformation& transformation) {
    const auto point = transformation.apply(CG::Point(x_, y_));
    x_ = point.x();
    y_ = point.y();
}

std::vector<std::pair<int, void*>> Vertex2f::layout() {
    return {{2, nullptr}};
}
