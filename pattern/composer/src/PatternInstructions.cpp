#include "initializers/PatternInstructions.h"

#include "initializers/Instructions.h"

using namespace Chrysalis;

Composer::PatternInstructions::PatternInstructions(args::patterns* selectedPatterns) {
    patterns = selectedPatterns;
    instructions = new PatternInstructionsContainer(
        Instructions::instructionsContainer->options(),
        Instructions::instructionsContainer->expressions(),
        patterns
    );
}

Composer::PatternInstructions::~PatternInstructions() {
    patterns = nullptr;
    instructions = nullptr;
}

std::vector<BaseInstruction*> Composer::PatternInstructions::operator<<(const std::initializer_list<std::vector<BasePatternInstruction*>>& patternInstructions) const {
    for (const auto& instructionsContainer: patternInstructions) {
        for (const auto& instruction: instructionsContainer) {
            instructions->add(instruction);
        }
    }
    return {instructions};
}