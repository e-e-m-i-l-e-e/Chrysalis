#include "Vertex3f.h"

using namespace Chrysalis;

Vertex3f::Vertex3f(const Point& point): Vertex3f(point, 0) {}

Vertex3f::Vertex3f(const Point& point, const float attribute): Vertex2f(point), attribute_(attribute) {}

Vertex3f::Vertex3f(const float x, const float y, const float attribute): Vertex2f(x, y), attribute_(attribute) {}

const float& Vertex3f::attribute() const {
    return attribute_;
}

std::vector<std::pair<int, void*>> Vertex3f::layout() {
    return {{2, nullptr}, {1, reinterpret_cast<void*>(2 * sizeof(float))}};
}