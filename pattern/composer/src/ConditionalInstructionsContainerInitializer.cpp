#include "initializers/ConditionalInstructionsContainerInitializer.h"

#include "instructions/BaseInstruction.h"
#include "instructions/ConditionalInstructionsContainer.h"
#include "initializers/Instructions.h"

using namespace Chrysalis::Composer;

ConditionalInstructionsContainerInitializer::ConditionalInstructionsContainerInitializer(const args::condition* condition)
    : condition_(condition) {}

ConditionalInstructionsContainerInitializer::True ConditionalInstructionsContainerInitializer::operator<<(std::initializer_list<std::vector<BaseInstruction*>>&& instructions) const {
    return True(condition_, std::move(instructions));
}

ConditionalInstructionsContainerInitializer::True::True(const args::condition* condition, std::initializer_list<std::vector<BaseInstruction*>>&& instructions)
    : condition_(condition), instructions_(instructions) {}

ConditionalInstructionsContainerInitializer::True::operator std::vector<Chrysalis::BaseInstruction*>() const {
    const auto trueInstructions = new BaseInstructionsContainer<BaseInstruction>(Instructions::instructionsContainer->options(), Instructions::instructionsContainer->expressions());
    for (const auto& instructions: instructions_) {
        for (const auto& instruction: instructions) {
            trueInstructions->add(instruction);
        }
    }
    const auto falseInstructions = new BaseInstructionsContainer<BaseInstruction>(Instructions::instructionsContainer->options(), Instructions::instructionsContainer->expressions());
    return {new ConditionalInstructionsContainer(condition_, trueInstructions, falseInstructions)};
}

std::vector<Chrysalis::BaseInstruction*> ConditionalInstructionsContainerInitializer::True::operator<<(std::initializer_list<std::vector<BaseInstruction*>>&& instructionBlocks) const {
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
