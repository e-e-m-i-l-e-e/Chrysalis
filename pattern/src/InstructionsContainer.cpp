#include "instructions/InstructionsContainer.h"

using namespace Chrysalis;

InstructionsContainer::InstructionsContainer(ExpressionsContainer* expressions): expressions_(expressions) {}

InstructionsContainer::~InstructionsContainer() {
    delete expressions_;
}

ExpressionsContainer* InstructionsContainer::expressions() const {
    return expressions_;
}
