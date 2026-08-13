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

Proxy::Name::Vector::Vector(args::name&& name, const args::vector* vector)
    : name_(std::move(name)), vector_(vector) {}

Proxy::Name::Vector::Line::Line(args::name&& name, const args::vector* vector, const args::line* line)
    : name_(std::move(name)), line_(line), vector_(vector) {}

Proxy::Name::Number::Number(args::name&& name, args::number&& number)
    : name_(std::move(name)), number_(std::move(number)) {}

Proxy::Name::operator const OptionArgument*() {
    return new OptionArgument(Composer::Instructions::instructionsContainer->options(), std::move(name_));
}

Proxy::Name::operator args::name() {
    return std::move(name_);
}

Proxy::Name::operator args::number() {
    return std::make_unique<ExpressionArgument>(Composer::Instructions::instructionsContainer->expressions(), std::move(name_));
}

Proxy::Name::operator const PatternPointArgument*() {
    return new PatternPointArgument(std::move(name_), new args::patterns(*Composer::PatternInstructions::patterns));
}

Proxy::Number::Point Proxy::Name::operator()(args::number&& number) {
    return Proxy::Number::Point(std::move(number), *this);
}
Proxy::Name::Vector::Line Proxy::Name::Vector::operator|(const args::line* line) {
    return Line(std::move(name_), vector_, line);
}

std::vector<BasePatternInstruction*> Proxy::Name::operator()(const double x, const double y) {
    return {new FreePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), std::move(name_), std::make_unique<Argument<double>>(x), std::make_unique<Argument<double>>(y))};
}

Proxy::Name::Vector::operator std::vector<BasePatternInstruction*>() {
    return {new RelativePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), std::move(name_), vector_, new args::optional<args::line>())};
}

Proxy::Name::Vector::Line::operator std::vector<BasePatternInstruction*>() {
    return {new RelativePointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), std::move(name_), vector_, new args::optional(line_))};
}

Proxy::Condition::Number Proxy::operator<<(const double value, Name&& name) {
    return Condition::Number(new OptionArgument(Composer::Instructions::instructionsContainer->options(), std::move(name)), std::make_unique<Argument<double>>(value));
}

Proxy::Name::Number Proxy::Name::operator=(const double value) {
    return Number(std::move(name_), std::make_unique<Argument<double>>(value));
}

Proxy::Name::Number Proxy::Name::operator=(args::number&& number) {
    return Number(*this, std::move(number));
}

const args::condition* Proxy::Name::operator<(Name&& other) {
    return new args::compare::Less(*this, other);
}

Proxy::Name::Number::operator std::vector<BaseInstruction*>() {
    return {new ExpressionInstruction(Composer::Instructions::instructionsContainer->expressions(), std::move(name_), std::move(number_))};
}