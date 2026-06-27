#include "arguments/SegmentArgument.h"

using namespace Chrysalis;

SegmentArgument::SegmentArgument(const PointArgument* pointFrom, const PointArgument* pointTo)
    : VectorArgument(pointFrom, pointTo), pointFrom_(pointFrom), pointTo_(pointTo) {}

SegmentArgument::~SegmentArgument() {
    delete pointFrom_;
    delete pointTo_;
}
