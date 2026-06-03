#include "../include/instructions/PatternInstructionsContainer.h"

Chrysalis::PatternInstructionsContainer::PatternInstructionsContainer(SelectedPatterns* patterns)
    : patterns_(patterns) {}

Chrysalis::PatternInstructionsContainer::~PatternInstructionsContainer() {
    delete patterns_;
}
