#include "proxies/NumberProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"

#include "instructions/DartInstruction.h"
#include "instructions/EdgeDartInstruction.h"
#include "instructions/UnfoldEdgeDartInstruction.h"

using namespace Chrysalis;

Proxy::Number::Number(const double value): number_(new Argument(value)) {}

Proxy::Number::Number(const args::number* number): number_(number) {}

Proxy::Number::Point::Point(const args::number* number, const PatternPointArgument* point)
    : number_(number), point_(point) {}

Proxy::Number::Point::Vector::Vector(const args::number* number, const PatternPointArgument* point, const args::vector* vector)
    : number_(number), vector_(vector), point_(point) {}

Proxy::Number::Vector::Segment::Segment(const args::number* number, const args::vector* vector, const args::segment* segment)
    : number_(number), vector_(vector), segment_(segment) {}

Proxy::Number::Segment::And::Segment::Segment(const args::number* number, const args::segment* segment1, const args::segment* segment2)
    : number_(number), segment1_(segment1), segment2_(segment2) {}

Proxy::Number::operator const args::number*() const {
    return number_;
}

Proxy::Number::Point::operator const BaseArgument<double>*() const {
    return number_;
}

Proxy::Number::Point::operator const PatternPointArgument*() const {
    return point_;
}

std::vector<BasePatternInstruction*> Proxy::Number::Point::Vector::operator>>(const args::vector* vector) const {
    return {new DartInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), point_, number_, vector_, vector)};
}

Proxy::Number::Vector::Segment::operator std::vector<BasePatternInstruction*>() const {
    return {new EdgeDartInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), segment_, vector_, number_, new args::optional<args::number>())};
}

Proxy::Number::Segment::And::Segment::operator std::vector<BasePatternInstruction*>() const {
    return {new UnfoldEdgeDartInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), segment1_, segment2_, number_)};
}
