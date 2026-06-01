#include "InstructionsContainer.h"

using namespace Chrysalis;

void InstructionsContainer::execute() const {
    call(&PatternInstructionsContainer::execute);
}