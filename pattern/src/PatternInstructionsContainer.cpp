#include "instructions/PatternInstructionsContainer.h"

using namespace Chrysalis;

PatternInstructionsContainer::PatternInstructionsContainer(args::patterns* patterns)
    : patterns_(patterns) {}

PatternInstructionsContainer::~PatternInstructionsContainer() {
    delete patterns_;
}
