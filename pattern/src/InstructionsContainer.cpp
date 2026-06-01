#include "InstructionsContainer.h"

using namespace Chrysalis;

void InstructionsContainer::execute() const {
    for (const auto& instruction: data_) instruction->execute();
}