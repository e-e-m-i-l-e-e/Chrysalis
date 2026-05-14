#include "PatternBuilder.h"

PatternBuilder::PatternBuilder(Pattern* pattern): pattern_(pattern) {}

PatternBuilder& PatternBuilder::addPoint(const std::string& name, double x, double y) {
    pattern_->addPoint(name, x, y);
    return *this;
}

PatternBuilder& PatternBuilder::addPoint(const std::string& fromPointName, const std::string& name,
                                         double angle, double length) {
    return *this;
}

PatternBuilder& PatternBuilder::addPoint(const std::string& fromPointName, const std::string& name,
                                         Direction direction, double length) {
    return *this;
}

PatternBuilder& PatternBuilder::nextPoint(const std::string& name, double angle, double length) {
    return *this;
}

PatternBuilder& PatternBuilder::nextPoint(const std::string& name, Direction direction, double length) {
    return *this;
}

OutlineBuilder PatternBuilder::editOutline() const {
    return OutlineBuilder(pattern_->editOutline());
}
