#include "PatternInstructionsContainer.h"

Chrysalis::PatternInstructionsContainer::PatternInstructionsContainer(PatternSpacesArgument* patternSpaces)
    : patternSpaces_(patternSpaces) {}

Chrysalis::PatternInstructionsContainer::~PatternInstructionsContainer() {
    BaseContainer::~BaseContainer();
    delete patternSpaces_;
}

void Chrysalis::PatternInstructionsContainer::execute() {
}
