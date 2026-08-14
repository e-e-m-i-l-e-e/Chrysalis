#include "initializers/ConditionalInstructionsContainerInitializer.h"

#include "instructions/BaseInstruction.h"
#include "instructions/ConditionalInstructionsContainer.h"
#include "initializers/Instructions.h"

using namespace Chrysalis::Composer;

ConditionalInstructionsContainerInitializer::ConditionalInstructionsContainerInitializer(const args::condition* condition)
    : condition_(condition) {}

ConditionalInstructionsContainerInitializer::True ConditionalInstructionsContainerInitializer::operator<<(std::initializer_list<BaseInstruction*>&& instructions) const {
    return True(condition_, std::move(instructions));
}

ConditionalInstructionsContainerInitializer::True::True(const args::condition* condition, std::initializer_list<BaseInstruction*>&& instructions)
    : condition_(condition), instructions_(instructions) {}

ConditionalInstructionsContainerInitializer::True::operator Chrysalis::BaseInstruction*() const {
    const auto trueInstructions = new BaseInstructionsContainer<BaseInstruction>(
        new OptionsContainer(Instructions::instructionsContainer->options()),
        new ExpressionsContainer(Instructions::instructionsContainer->expressions())
    );
    for (const auto& instruction: instructions_) {
        trueInstructions->add(instruction);
    }
    const auto falseInstructions = new BaseInstructionsContainer<BaseInstruction>(
        new OptionsContainer(Instructions::instructionsContainer->options()),
        new ExpressionsContainer(Instructions::instructionsContainer->expressions())
    );
    return new ConditionalInstructionsContainer(condition_, trueInstructions, falseInstructions);
}

Chrysalis::BaseInstruction* ConditionalInstructionsContainerInitializer::True::operator<<(std::initializer_list<BaseInstruction*>&& instructionBlocks) const {
    const auto trueInstructions = new BaseInstructionsContainer<BaseInstruction>(
        new OptionsContainer(Instructions::instructionsContainer->options()),
        new ExpressionsContainer(Instructions::instructionsContainer->expressions())
    );
    for (const auto& instruction: instructions_) {
        trueInstructions->add(instruction);
    }
    const auto falseInstructions = new BaseInstructionsContainer<BaseInstruction>(
        new OptionsContainer(Instructions::instructionsContainer->options()),
        new ExpressionsContainer(Instructions::instructionsContainer->expressions())
    );
    for (const auto& instruction: instructionBlocks) {
        falseInstructions->add(instruction);
    }
    return new ConditionalInstructionsContainer(condition_, trueInstructions, falseInstructions);
}
