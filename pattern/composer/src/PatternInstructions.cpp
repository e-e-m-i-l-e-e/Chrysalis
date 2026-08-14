#include "initializers/PatternInstructions.h"

#include "initializers/Instructions.h"

using namespace Chrysalis;

Composer::PatternInstructions::PatternInstructions(args::patterns* selectedPatterns) {
    patterns = selectedPatterns;
    instructions = new PatternInstructionsContainer(
        new OptionsContainer(Instructions::instructionsContainer->options()),
        new ExpressionsContainer(Instructions::instructionsContainer->expressions()),
        patterns
    );
}

Composer::PatternInstructions::~PatternInstructions() {
    patterns = nullptr;
    instructions = nullptr;
}

BaseInstruction* Composer::PatternInstructions::operator<<(std::initializer_list<BasePatternInstruction*>&& patternInstructions) const {
    for (const auto& instruction: patternInstructions) {
        instructions->add(instruction);
    }
    return instructions;
}