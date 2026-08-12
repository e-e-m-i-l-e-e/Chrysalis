#include "proxies/NameProxy.h"

#include "arguments/ComparisonArgument.h"
#include "arguments/OptionArgument.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"
#include "instructions/ExpressionInstruction.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/RelativePointInstruction.h"

using namespace Chrysalis;

Proxy::Name::Name(const std::string& name): name_(new Argument(name)) {}

Proxy::Name::Vector::Vector(const args::name* name, const args::vector* vector)
    : name_(name), vector_(vector) {}

Proxy::Name::Vector::Line::Line(const args::name* name, const args::vector* vector, const args::line* line)
    : name_(name), line_(line), vector_(vector) {}

Proxy::Name::Number::Number(const args::name* name, args::number&& number)
    : name_(name), number_(std::move(number)) {}

Proxy::Name::operator const OptionArgument*() const {
    return new OptionArgument(Composer::Instructions::instructionsContainer->options(), name_);
}

Proxy::Name::operator const Argument<std::string>*() const {
    return name_;
}

Proxy::Name::operator args::number() {
    return std::make_unique<ExpressionArgument>(Composer::Instructions::instructionsContainer->expressions(), name_);
}

Proxy::Name::operator const PatternPointArgument*() const {
    return new PatternPointArgument(name_, new args::patterns(*Composer::PatternInstructions::patterns));
}

Proxy::Number::Point Proxy::Name::operator()(args::number&& number) const {
    return Proxy::Number::Point(std::move(number), *this);
}
Proxy::Name::Vector::Line Proxy::Name::Vector::operator|(const args::line* line) const {
    return Line(name_, vector_, line);
}

std::vector<BasePatternInstruction*> Proxy::Name::operator()(const double x, const double y) const {
    return {new FreePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), name_, std::make_unique<const Argument<double>>(x), std::make_unique<const Argument<double>>(y))};
}

Proxy::Name::Vector::operator std::vector<BasePatternInstruction*>() const {
    return {new RelativePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), name_, vector_, new args::optional<args::line>())};
}

Proxy::Name::Vector::Line::operator std::vector<BasePatternInstruction*>() const {
    return {new RelativePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), name_, vector_, new args::optional(line_))};
}

Proxy::Condition::Number Proxy::operator<<(const double value, const Name& name) {
    return Condition::Number(new OptionArgument(Composer::Instructions::instructionsContainer->options(), name), std::make_unique<const Argument<double>>(value));
}

Proxy::Name::Number Proxy::Name::operator=(const double value) const {
    return Number(name_, std::make_unique<const Argument<double>>(value));
}

Proxy::Name::Number Proxy::Name::operator=(args::number&& number) const {
    return Number(*this, std::move(number));
}

const args::condition* Proxy::Name::operator<(Name&& other) {
    return new args::compare::Less(*this, other);
}

Proxy::Name::Number::operator std::vector<BaseInstruction*>() {
    return {new ExpressionInstruction(Composer::Instructions::instructionsContainer->expressions(), name_, std::move(number_))};
}