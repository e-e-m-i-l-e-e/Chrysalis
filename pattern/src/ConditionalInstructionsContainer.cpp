#include "instructions/ConditionalInstructionsContainer.h"

using namespace Chrysalis;

ConditionalInstructionsContainer::ConditionalInstructionsContainer(const args::condition* condition,
                                                                   const BaseInstructionsContainer<BaseInstruction>* positive,
                                                                   const BaseInstructionsContainer<BaseInstruction>* negative)
    : condition_(condition), positive_(positive), negative_(negative) {}

ConditionalInstructionsContainer::~ConditionalInstructionsContainer() {
    delete condition_;
    delete positive_;
    delete negative_;
}

void ConditionalInstructionsContainer::execute() {
    if (condition_->get()) {
        for (const auto& instruction: *positive_) {
            instruction->execute();
        }
    } else {
        for (const auto& instruction: *negative_) {
            instruction->execute();
        }
    }
}
