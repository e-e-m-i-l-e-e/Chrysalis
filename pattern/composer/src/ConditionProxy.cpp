#include "proxies/ConditionProxy.h"

#include "arguments/Argument.h"

using namespace Chrysalis;

Proxy::Condition::Number::Number(const args::condition* condition, const args::number* number)
    : condition_(condition), number_(number) {}

const args::conditional& Proxy::Condition::Number::operator>>(const double value) const {
    return *new args::conditional(condition_, number_, new Argument(value));
}