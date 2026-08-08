#include "arguments/SegmentArgument.h"

using namespace Chrysalis;

SegmentArgument::SegmentArgument(const args::point* origin, const args::point* destination)
    : VectorArgument(origin, destination), destination_(destination) {}

SegmentArgument::~SegmentArgument() {
    delete destination_;
}

const args::point* SegmentArgument::destination() const {
    return destination_;
}

SegmentArgument::operator CG::Segment() const {
    return CG::Segment(*origin(), *destination());
}
