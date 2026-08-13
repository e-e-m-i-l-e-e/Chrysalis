#include "proxies/VectorProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"

#include "instructions/CurveInstruction.h"

using namespace Chrysalis;

Proxy::Vector::Vector(const args::point* origin, args::number&& angle, args::number&& length)
    : vector_(new VectorArgument(origin, std::move(angle), std::move(length))) {}

Proxy::Vector::Vector(const args::point* origin, args::number&& angle, const double length)
    : vector_(new VectorArgument(origin, std::move(angle), std::make_unique<Argument<double>>(length))) {}

Proxy::Vector::Vector(const args::point* origin, const double angle, args::number&& length)
    : vector_(new VectorArgument(origin, std::make_unique<Argument<double>>(angle), std::move(length))) {}

Proxy::Vector::Vector(const args::point* origin, const double angle, const double length)
    : vector_(new VectorArgument(origin, std::make_unique<Argument<double>>(angle), std::make_unique<Argument<double>>(length))) {}

Proxy::Vector::Vector(args::number&& angle, args::number&& length)
    : vector_(new VectorArgument(std::move(angle), std::move(length))) {}

Proxy::Vector::Vector(const double angle, args::number&& length)
    : vector_(new VectorArgument(std::make_unique<Argument<double>>(angle), std::move(length))) {}

Proxy::Vector::Vector(const double angle, const double length)
    : vector_(new VectorArgument(std::make_unique<Argument<double>>(angle), std::make_unique<Argument<double>>(length))) {}

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

Proxy::Name::Vector Proxy::Vector::And::name(args::name&& name) const {
    return Name::Vector(std::move(name), vector_);
}

Proxy::Vector::And* Proxy::Vector::And::operator->() {
    return this;
}

Proxy::Number::Point::Vector Proxy::Vector::operator<<(Number::Point&& args) const {
    return Number::Point::Vector(args, args, *this);
}

Proxy::Point::Vector Proxy::Vector::operator>>(const PatternPointArgument* point) const {
    return Point::Vector(point, vector_);
}

Proxy::Number::Vector::Segment Proxy::Vector::Segment::operator()(const double number) const {
    return Number::Vector::Segment(std::make_unique<Argument<double>>(number), vector_, segment_);
}

Proxy::Vector::And::Vector::operator std::vector<BasePatternInstruction*>() const {
    return {new CurveInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), vector1_, vector2_, new args::container<PatternPointArgument>())};
}
