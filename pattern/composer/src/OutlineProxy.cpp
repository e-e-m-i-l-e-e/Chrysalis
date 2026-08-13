#include "proxies/OutlineProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"
#include "instructions/BuildOutlineInstruction.h"

using namespace Chrysalis;

Proxy::Outline::Outline(const std::string& name)
    : name_(name) {}

Proxy::Outline::Point::Point(const std::string& name, const PatternPointArgument* point)
    : name_(name) {
    points_.push_back(point);
}

Proxy::Outline::Point Proxy::Outline::operator>>(const PatternPointArgument* point) const {
    return Point(name_, point);
}

Proxy::Outline::Point& Proxy::Outline::Point::operator>>(const PatternPointArgument* point) {
    points_.push_back(point);
    return *this;
}

Proxy::Outline::Point::operator const std::vector<BasePatternInstruction*>() const {
    const auto pointsContainer = new args::container<const PatternPointArgument>();
    for (const auto& point: points_) {
        pointsContainer->add(point);
    }
    return std::vector<BasePatternInstruction*>{
        new BuildOutlineInstruction(
            Composer::Instructions::space,
            new args::patterns(*Composer::PatternInstructions::patterns),
            std::make_unique<Argument<std::string>>(name_),
            pointsContainer
        )
    };
}
