#ifndef CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H

#include "SelectedPatterns.h"
#include "BasePatternInstruction.h"
#include "BaseInstructionsContainer.h"

namespace Chrysalis {
    class SERIALIZABLE(PatternInstructionsContainer): public BaseInstructionsContainer<BasePatternInstruction> {
        PROVIDE_SERIALIZATION_ACCESS(PatternInstructionsContainer)
    public:
        explicit PatternInstructionsContainer(SelectedPatterns* patterns);
        ~PatternInstructionsContainer() override;
    private:
        /// @uml{composition[]}
        SelectedPatterns* patterns_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(PatternInstructionsContainer, BaseInstructionsContainer<BasePatternInstruction>, patterns_)
}

#endif //CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H