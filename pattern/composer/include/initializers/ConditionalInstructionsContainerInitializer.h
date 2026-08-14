#ifndef CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINERINITIALIZER_H
#define CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINERINITIALIZER_H

#include <vector>
#include <initializer_list>

#include "instructions/BaseInstruction.h"
#include "arguments/ConditionalArgument.h"

namespace Chrysalis::Composer {
    class ConditionalInstructionsContainerInitializer {
    public:
        class True;
        explicit ConditionalInstructionsContainerInitializer(const args::condition* condition);
        True operator<<(std::initializer_list<BaseInstruction*>&& instructions) const;
    private:
        const args::condition* condition_;
    };
    class ConditionalInstructionsContainerInitializer::True {
    public:
        explicit True(const args::condition* condition, std::initializer_list<BaseInstruction*>&& instructions);
        operator Chrysalis::BaseInstruction*() const;
        BaseInstruction* operator<<(std::initializer_list<BaseInstruction*>&& instructionBlocks) const;
    private:
        const args::condition* condition_;
        const std::initializer_list<BaseInstruction*> instructions_;
    };
}

#endif //CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINERINITIALIZER_H
