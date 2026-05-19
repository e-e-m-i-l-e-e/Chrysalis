#include "PatternBuilder.h"

using namespace PB;

PatternBuilder::PatternBuilder(Space* space, Pattern* pattern): space_(space), pattern_(pattern) {}

PatternBuilder& PatternBuilder::addPoint(const std::string& name, const double x, const double y) {
    space_->addPoint(name, x, y);
    return *this;
}

PatternBuilder& PatternBuilder::addPoint(const std::string& fromPointName, const std::string& name,
                                         const double angle, const double length) {
    space_->addPoint(fromPointName, name, angle, length);
    return *this;
}

PatternBuilder& PatternBuilder::addPoint(const std::string& fromPointName, const std::string& name,
                                         const Space::Direction direction, const double length) {
    space_->addPoint(fromPointName, name, direction, length);
    return *this;
}

PatternBuilder& PatternBuilder::nextPoint(const std::string& name, const double angle, const double length) {
    space_->addPoint(name, angle, length);
    return *this;
}

PatternBuilder& PatternBuilder::nextPoint(const std::string& name, const Space::Direction direction, const double length) {
    space_->nextPoint(name, direction, length);
    return *this;
}

OutlineBuilder PatternBuilder::editOutline() const {
    return OutlineBuilder(pattern_->editOutline());
}

// std::vector<int> PatternBuilder::getEBO() const {
//     return {0, 1, 1, 2, 2, 3, 3, 0};
// }

std::vector<SpaceVertex> PatternBuilder::getVBO() const {
    return space_->getVBO();
}

Space& PatternBuilder::getSpace() const
{
    return *space_;
}

// std::vector<DistancedVertex> PatternBuilder::getDistancedVBO() const {
//     return space_->getDistancedVBO();
// }
