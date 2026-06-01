#include "InstructionsContainer.h"

using namespace Chrysalis;

void InstructionsContainer::execute() {
    if (!nextInstruction_.has_value() && begin() != end()) {
        nextInstruction_ = begin();
    }
    while (nextInstruction_ != end()) {
        (*nextInstruction_.value())->execute();
        ++nextInstruction_.value();
    }
}
