#include "Vertex2f.h"

using namespace Chrysalis;

Vertex2f::Vertex2f(float x, float y): x_(x), y_(y) {}

const float& Vertex2f::x() const {
    return x_;
}

const float& Vertex2f::y() const {
    return y_;
}

std::vector<std::pair<int, void*>> Vertex2f::getLayout()
{
    return {{2, nullptr}};
}
