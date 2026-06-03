#include "OutlineContainer.h"

void Chrysalis::OutlineContainer::add(Outline* item) {
    BaseContainer::add(item);
    outlines_[item->getName()] = item;
}

bool Chrysalis::OutlineContainer::has(const std::string& name) const {
    return outlines_.contains(name);
}

Chrysalis::Outline* Chrysalis::OutlineContainer::get(const std::string& name) const {
    return outlines_.at(name);
}
