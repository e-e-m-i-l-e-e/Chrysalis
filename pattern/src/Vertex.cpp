#include "Vertex.h"

Vertex::Vertex(const float x, const float y): x_(x), y_(y) {}

float Vertex::x() const {
    return x_;
}

float Vertex::y() const {
    return y_;
}

std::vector<Vertex::Layout> Vertex::getLayout() {
    return {{2, nullptr}};
}