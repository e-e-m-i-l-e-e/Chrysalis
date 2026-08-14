#include "proxies/PointProxy.h"

#include "proxies/VectorProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"
#include "instructions/MovePointInstruction.h"

using namespace Chrysalis;

Proxy::Point::Point(const PatternPointArgument* point): point_(point) {}

Proxy::Point::Vector::Vector(const PatternPointArgument* point, const args::vector* vector)
    : vector_(vector), point_(point) {}

Proxy::Point::Vector::And::Vector::Vector(const PatternPointArgument* point, const args::vector* vector1, const args::vector* vector2)
    : point_(point), vector1_(vector1), vector2_(vector2) {}

Proxy::Point::operator const PatternPointArgument*() const {
    return point_;
}

Proxy::Point::Vector::And::Vector Proxy::Point::Vector::operator<<(const args::vector* vector) const {
    return And::Vector(point_, vector_, vector);
}

Proxy::Number Proxy::Point::operator()(args::number&& number) const {
    return Proxy::Number(std::move(number));
}

Proxy::Point::Vector::operator MovePointInstruction*() const {
    return new MovePointInstruction(
        Composer::Instructions::space,
        new args::patterns(*Composer::PatternInstructions::patterns),
        point_, vector_, new args::optional<args::vector>()
    );
}

Proxy::Point::Vector::And::Vector::operator MovePointInstruction*() const {
    return new MovePointInstruction(
        Composer::Instructions::space,
        new args::patterns(*Composer::PatternInstructions::patterns),
        point_, vector1_, new args::optional(vector2_)
    );
}
