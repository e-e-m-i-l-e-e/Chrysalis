#include "proxies/SegmentProxy.h"

using namespace Chrysalis;

Proxy::Segment::Segment(args::segment* segment): segment_(segment) {}

Proxy::Segment::And::And(const args::segment* segment): segment_(segment) {}

Proxy::Segment::And::Segment::Segment(const args::segment* segment1, const args::segment* segment2)
    : segment1_(segment1), segment2_(segment2) {}

Proxy::Segment::operator SegmentArgument*() const {
    return segment_;
}

Proxy::Segment::And Proxy::Segment::operator->() const {
    return And(segment_);
}

Proxy::Segment::And::Segment Proxy::Segment::And::seg(const args::segment* segment) const {
    return Segment(segment_, segment);
}

Proxy::Segment::And* Proxy::Segment::And::operator->() {
    return this;
}

Proxy::Number::Segment::And::Segment Proxy::Segment::And::Segment::operator()(args::number&& number) const {
    return Number::Segment::And::Segment(std::move(number), segment1_, segment2_);
}

Proxy::Line::Lines Proxy::Segment::operator|(const args::container<args::line>* lines) const {
    return Line::Lines(segment_, lines);
}

Proxy::Point::Vector Proxy::Segment::operator>>(const PatternPointArgument* point) const {
    return Point::Vector(point, segment_);
}

Proxy::Vector::And::Vector Proxy::Segment::operator&(const args::vector* vector) const {
    return Vector::And::Vector(segment_, vector);
}

Proxy::Vector::Segment Proxy::Segment::And::vec(const args::vector* vector) const {
    return Vector::Segment(vector, segment_);
}
