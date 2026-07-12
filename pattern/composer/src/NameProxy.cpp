#include "proxies/NameProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/RelativePointInstruction.h"

using namespace Chrysalis;

Proxy::Name::Name(const std::string& name): name_(new Argument(name)) {}

Proxy::Name::Vector::Vector(const args::name* name, const args::vector* vector)
    : name_(name), vector_(vector) {}

Proxy::Name::Vector::Line::Line(const args::name* name, const args::vector* vector, const args::line* line)
    : name_(name), line_(line), vector_(vector) {}

Proxy::Name::operator const Argument<std::string>*() const {
    return name_;
}

Proxy::Name::operator const PatternPointArgument*() const {
    return new PatternPointArgument(name_, new args::patterns(*Composer::PatternInstructions::patterns));
}

Proxy::Number::Point Proxy::Name::operator()(const args::number& number) const {
    return Number::Point(&number, *this);
}
Proxy::Name::Vector::Line Proxy::Name::Vector::operator|(const args::line* line) const {
    return Line(name_, vector_, line);
}

std::vector<BasePatternInstruction*> Proxy::Name::operator()(const double x, const double y) const {
    return {new FreePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), name_, new Argument(x), new Argument(y))};
}

Proxy::Name::Vector::operator std::vector<BasePatternInstruction*>() const {
    return {new RelativePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), name_, vector_, new args::optional<args::line>())};
}

Proxy::Name::Vector::Line::operator std::vector<BasePatternInstruction*>() const {
    return {new RelativePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), name_, vector_, new args::optional(line_))};
}