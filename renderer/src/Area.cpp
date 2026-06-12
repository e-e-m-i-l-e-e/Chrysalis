#include "Area.h"

using namespace Chrysalis;

Area::Area(): x_(0), y_(0), width_(0), height_(0) {}

Area::Area(const float x, const float y, const float width, const float height)
    : x_(x), y_(y), width_(width), height_(height) {}

const float& Area::x() const {
    return x_;
}

const float& Area::y() const {
    return y_;
}

const float& Area::width() const {
    return width_;
}

const float& Area::height() const {
    return height_;
}

void Area::scale(const float scaleFactor) {
    width_ /= scaleFactor;
    height_ /= scaleFactor;
}

void Area::offset(const float deltaX, const float deltaY) {
    x_ -= deltaX * width();
    y_ -= deltaY * height();
}

void Area::setSize(const float width, const float height) {
    width_ = width;
    height_ = height;
}
