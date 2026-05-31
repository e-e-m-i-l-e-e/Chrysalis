#include "PatternSpacesInstructions.h"

void Chrysalis::PatternSpacesInstructions::addInstruction(BasePatternSpacesInstruction* instruction) {
    instructions_.push_back(instruction);
}

void Chrysalis::PatternSpacesInstructions::reset()
{
}

bool Chrysalis::PatternSpacesInstructions::isValid() {
    return true;
}

void Chrysalis::PatternSpacesInstructions::execute() {
    for (const auto& instruction : instructions_) {
        instruction->execute();
    }
}