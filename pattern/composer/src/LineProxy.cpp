#include "proxies/LineProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"

using namespace Chrysalis;

Proxy::Line::Line(const args::line* line)
    : line_(line) {}

Proxy::Line::Lines::Lines(const args::line* line, const args::container<args::line>* lines)
    : line_(line), lines_(lines) {}

Proxy::Line::Lines::And::And(const args::line* line, const args::container<args::line>* lines)
    : line_(line), lines_(lines) {}

Proxy::Line::Lines::And::Names::Names(const args::line* line, const args::container<args::line>* lines,
                                           const args::container<Argument<std::string>>* names)
    : line_(line), lines_(lines), names_(names) {}

Proxy::Line::Lines Proxy::Line::operator|(const args::container<args::line>* lines) const {
    return Lines(line_, lines);
}

Proxy::Line::Lines::And Proxy::Line::Lines::operator->() const {
    return And(line_, lines_);
}

Proxy::Line::Lines::And::Names Proxy::Line::Lines::And::names(
    const args::container<Argument<std::string>>* names) const {
    return Names(line_, lines_, names);
}

Proxy::Line::Lines::And* Proxy::Line::Lines::And::operator->() {
    return this;
}

Proxy::Line::Lines::And::Names::operator std::vector<BasePatternInstruction*>() const {
    return {new IntersectionPointInstruction(Composer::Instructions::space, new args::patterns(*Composer::PatternInstructions::patterns), line_, names_, lines_)};
}
