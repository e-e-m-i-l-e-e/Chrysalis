#include "ParametersContainer.h"

using namespace Chrysalis;

void ParametersContainer::add(Parameter* item) {
    BaseContainer::add(item);
    parametersMap_[item->getName()] = item;
    if (item->hasAlias()) {
        parametersMap_[item->getAlias()] = item;
    }
}

Parameter* ParametersContainer::get(const std::string& name) const {
    return parametersMap_.at(name);
}
