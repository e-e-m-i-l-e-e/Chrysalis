#include "instructions/PatternInstructionsContainer.h"

using namespace Chrysalis;

PatternInstructionsContainer::PatternInstructionsContainer(OptionsContainer* options, ExpressionsContainer* expressions,
                                                           args::patterns* patterns)
    : BaseInstructionsContainer(options, expressions), patterns_(patterns) {}

PatternInstructionsContainer::~PatternInstructionsContainer() {
    delete patterns_;
}
