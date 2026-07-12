#include "initializers/ConditionalInstructionsContainerInitializer.h"

#include "instructions/ConditionalInstructionsContainer.h"
#include "initializers/Instructions.h"

using namespace Chrysalis::Composer;

ConditionalInstructionsContainerInitializer::ConditionalInstructionsContainerInitializer(const args::condition* condition)
    : condition_(condition) {}

ConditionalInstructionsContainerInitializer::True ConditionalInstructionsContainerInitializer::operator<<(const std::initializer_list<std::vector<BaseInstruction*>>& instructions) const {
    return True(condition_, instructions);
}

ConditionalInstructionsContainerInitializer::True::True(const args::condition* condition, const std::initializer_list<std::vector<BaseInstruction*>>& instructions)
    : condition_(condition), instructions_(instructions) {}

std::vector<Chrysalis::BaseInstruction*> ConditionalInstructionsContainerInitializer::True::operator<<(const std::initializer_list<std::vector<BaseInstruction*>>& instructionBlocks) const {
    const auto trueInstructions = new BaseInstructionsContainer<BaseInstruction>(Instructions::instructionsContainer->options(), Instructions::instructionsContainer->expressions());
    for (const auto& instructions: instructions_) {
        for (const auto& instruction: instructions) {
            trueInstructions->add(instruction);
        }
    }
    const auto falseInstructions = new BaseInstructionsContainer<BaseInstruction>(Instructions::instructionsContainer->options(), Instructions::instructionsContainer->expressions());
    for (const auto& instructions: instructionBlocks) {
        for (auto& instruction: instructions) {
            falseInstructions->add(instruction);
        }
    }
    return {new ConditionalInstructionsContainer(condition_, trueInstructions, falseInstructions)};
}
