#include "proxies/OutlineProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"
#include "instructions/BuildOutlineInstruction.h"

using namespace Chrysalis;

Proxy::Outline::Outline(const std::string& name)
    : name_(new Argument(name)) {}

Proxy::Outline::Point::Point(const args::name* name, const PatternPointArgument* point)
    : name_(name), point_(point) {}

Proxy::Outline::Point Proxy::Outline::operator>>(const PatternPointArgument* point) const {
    return Point(name_, point);
}

Proxy::Outline::Point& Proxy::Outline::Point::operator>>(const PatternPointArgument* point) {
    instructions_.push_back(new BuildOutlineInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), new Argument(*name_), point));
    return *this;
}

Proxy::Outline::Point::operator const std::vector<BasePatternInstruction*>&() const {
    return instructions_;
}
