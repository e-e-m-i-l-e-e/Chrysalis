#ifndef CHRYSALIS_INSTRUCTIONSCONTAINER_H
#define CHRYSALIS_INSTRUCTIONSCONTAINER_H

#include "Expression.h"
#include "instructions/BaseInstructionsContainer.h"

namespace Chrysalis {
    class InstructionsContainer: public BaseInstructionsContainer<BaseInstruction> {
        PROVIDE_SERIALIZATION_ACCESS(InstructionsContainer)
    public:
        explicit InstructionsContainer(ExpressionsContainer* expressions);
        ~InstructionsContainer() override;

        [[nodiscard]] ExpressionsContainer* expressions() const;
    private:
        /// @uml{composition}
        ExpressionsContainer* expressions_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(InstructionsContainer, BaseInstructionsContainer<BaseInstruction>, expressions_)
}

#endif //CHRYSALIS_INSTRUCTIONSCONTAINER_H