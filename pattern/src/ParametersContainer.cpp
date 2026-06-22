#include "ParametersContainer.h"

using namespace Chrysalis;

void ParametersContainer::add(Parameter* item) {
    BaseInputContainer::add(item->getName(), item);
}