#ifndef CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H

#include "BasePatternInstruction.h"
#include "BaseInstructionsContainer.h"
#include "arguments/PatternsContainerArgument.h"

namespace Chrysalis {
    class PatternInstructionsContainer: public BaseInstructionsContainer<BasePatternInstruction> {
        PROVIDE_SERIALIZATION_ACCESS(PatternInstructionsContainer)
    public:
        explicit PatternInstructionsContainer(args::patterns* patterns);
        ~PatternInstructionsContainer() override;
    private:
        /// @uml{composition[]}
        args::patterns* patterns_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(PatternInstructionsContainer, BaseInstructionsContainer<BasePatternInstruction>, patterns_)
}

#endif //CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H