#ifndef CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINER_H

#include "BaseInstructionsContainer.h"
#include "instructions/BaseInstruction.h"
#include "arguments/ConditionalArgument.h"

namespace Chrysalis {
    class ConditionalInstructionsContainer: public BaseInstruction {
        PROVIDE_SERIALIZATION_ACCESS(ConditionalInstructionsContainer)
    public:
        explicit ConditionalInstructionsContainer(const args::condition* condition,
                                                  const BaseInstructionsContainer<BaseInstruction>* positive,
                                                  const BaseInstructionsContainer<BaseInstruction>* negative);
        ~ConditionalInstructionsContainer() override;

        void execute() override;
    private:
        const args::condition* condition_;
        const BaseInstructionsContainer<BaseInstruction>* positive_;
        const BaseInstructionsContainer<BaseInstruction>* negative_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ConditionalInstructionsContainer, BaseInstruction, condition_, positive_, negative_)
}

#endif //CHRYSALIS_CONDITIONALINSTRUCTIONSCONTAINER_H