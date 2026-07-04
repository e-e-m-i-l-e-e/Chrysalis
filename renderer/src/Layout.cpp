#include "Layout.h"

Chrysalis::Layout::Layout(const size_t offset, const size_t count): offset_(offset), count_(count) {}

const size_t& Chrysalis::Layout::offset() const {
    return offset_;
}

const size_t& Chrysalis::Layout::count() const {
    return count_;
}
