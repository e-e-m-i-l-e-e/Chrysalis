#include "SpaceVertex.h"

SpaceVertex::SpaceVertex(const float x, const float y, const float distance)
    : Vertex(x, y), distance_(distance) {}

float SpaceVertex::distance() const {
    return distance_;
}

std::vector<Vertex::Layout> SpaceVertex::getLayout() {
    auto layout = Vertex::getLayout();
    layout.push_back({1, reinterpret_cast<void*>(2 * sizeof(float))});
    return layout;
}
