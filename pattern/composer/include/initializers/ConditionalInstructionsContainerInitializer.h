#ifndef CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINERINITIALIZER_H
#define CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINERINITIALIZER_H

#include "arguments/ConditionalArgument.h"
#include "instructions/BaseInstruction.h"

namespace Chrysalis::Composer {
    class ConditionalInstructionsContainerInitializer {
    public:
        class True;
        explicit ConditionalInstructionsContainerInitializer(const args::condition* condition);
        True operator<<(const std::initializer_list<std::vector<BaseInstruction*>>& instructions) const;
    private:
        const args::condition* condition_;
    };
    class ConditionalInstructionsContainerInitializer::True {
    public:
        explicit True(const args::condition* condition, const std::initializer_list<std::vector<BaseInstruction*>>& instructions);
        std::vector<BaseInstruction*> operator<<(const std::initializer_list<std::vector<BaseInstruction*>>& instructionBlocks) const;
    private:
        const args::condition* condition_;
        const std::initializer_list<std::vector<BaseInstruction*>> instructions_;
    };
}

#endif //CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINERINITIALIZER_H
