#include "proxies/VectorProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"

#include "instructions/CurveInstruction.h"

using namespace Chrysalis;

Proxy::Vector::Vector(const args::point* origin, const args::number& angle, const args::number& length)
    : vector_(new VectorArgument(origin, &angle, &length)) {}

Proxy::Vector::Vector(const args::point* origin, const args::number* angle, const double length)
    : vector_(new VectorArgument(origin, angle, new Argument(length))) {}

Proxy::Vector::Vector(const args::point* origin, const double angle, const args::number& length)
    : vector_(new VectorArgument(origin, new Argument(angle), &length)) {}

Proxy::Vector::Vector(const args::point* origin, const double angle, const double length)
    : vector_(new VectorArgument(origin, new Argument(angle), new Argument(length))) {}

Proxy::Vector::Vector(const args::number& angle, const args::number& length)
    : vector_(new VectorArgument(&angle, &length)) {}

Proxy::Vector::Vector(const double angle, const args::number& length)
    : vector_(new VectorArgument(new Argument(angle), &length)) {}

Proxy::Vector::Vector(const double angle, const double length)
    : vector_(new VectorArgument(new Argument(angle), new Argument(length))) {}

Proxy::Vector::And::And(const VectorArgument* vector): vector_(vector) {}

Proxy::Vector::And::Vector::Vector(const VectorArgument* vector1, const VectorArgument* vector2)
    : vector1_(vector1), vector2_(vector2) {}

Proxy::Vector::Segment::Segment(const VectorArgument* vector, const args::segment* segment)
    : vector_(vector), segment_(segment) {}

Proxy::Vector::operator const VectorArgument*() const {
    return vector_;
}

Proxy::Vector::And Proxy::Vector::operator->() const {
    return And(vector_);
}

Proxy::Name::Vector Proxy::Vector::And::name(const args::name* name) const {
    return Name::Vector(name, vector_);
}

Proxy::Vector::And* Proxy::Vector::And::operator->() {
    return this;
}

Proxy::Number::Point::Vector Proxy::Vector::operator<<(const Number::Point args) const {
    return Number::Point::Vector(args, args, *this);
}

Proxy::Point::Vector Proxy::Vector::operator>>(const PatternPointArgument* point) const {
    return Point::Vector(point, vector_);
}

Proxy::Number::Vector::Segment Proxy::Vector::Segment::operator()(const double number) const {
    return Number::Vector::Segment(new Argument(number), vector_, segment_);
}

Proxy::Vector::And::Vector::operator std::vector<BasePatternInstruction*>() const {
    return {new CurveInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), vector1_, vector2_, new args::container<PatternPointArgument>())};
}
