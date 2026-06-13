#include "PatternsContainer.h"

void Chrysalis::PatternsContainer::add(Pattern* item) {
    BaseContainer::add(item);
    patterns_[item->getName()] = item;
}

Chrysalis::Pattern* Chrysalis::PatternsContainer::get(const std::string& name) const {
    return patterns_.at(name);
}
