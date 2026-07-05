#ifndef CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H

#include "arguments/PatternsContainerArgument.h"
#include "instructions/BasePatternInstruction.h"
#include "instructions/BaseInstructionsContainer.h"

namespace Chrysalis {
    class PatternInstructionsContainer: public BaseInstructionsContainer<BasePatternInstruction> {
        PROVIDE_SERIALIZATION_ACCESS(PatternInstructionsContainer)
    public:
        explicit PatternInstructionsContainer(args::patterns* patterns);
        ~PatternInstructionsContainer() override;

        bool isValid() override;
    private:
        /// @uml{composition}
        args::patterns* patterns_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(PatternInstructionsContainer, BaseInstructionsContainer<BasePatternInstruction>, patterns_)
}

#endif //CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H