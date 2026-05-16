#include "DistancedVertex.h"

DistancedVertex::DistancedVertex(const float x, const float y, const float distance)
    : Vertex(x, y), distance_(distance) {}

float DistancedVertex::distance() const {
    return distance_;
}
