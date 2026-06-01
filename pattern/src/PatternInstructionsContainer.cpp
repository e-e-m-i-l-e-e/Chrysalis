#include "PatternInstructionsContainer.h"

Chrysalis::PatternInstructionsContainer::PatternInstructionsContainer(SelectedPatterns* patterns)
    : patterns_(patterns) {}

Chrysalis::PatternInstructionsContainer::~PatternInstructionsContainer() {
    delete patterns_;
}

void Chrysalis::PatternInstructionsContainer::execute() const {
    call(&BasePatternInstruction::execute);
}
