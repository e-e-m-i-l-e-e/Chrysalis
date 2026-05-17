#include "SpaceVertex.h"

SpaceVertex::SpaceVertex(const float x, const float y, const float distance)
    : Vertex(x, y), distance_(distance) {}

float SpaceVertex::distance() const {
    return distance_;
}
