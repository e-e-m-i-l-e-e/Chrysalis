#include "proxies/ConditionProxy.h"

#include "arguments/Argument.h"

using namespace Chrysalis;

Proxy::Condition::Number::Number(const args::condition* condition, args::number&& number)
    : condition_(condition), number_(std::move(number)) {}

args::number Proxy::Condition::Number::operator>>(const double value) {
    return std::make_unique<args::conditional>(condition_, std::move(number_), std::make_unique<Argument<double>>(value));
}