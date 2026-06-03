#ifndef CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H

#include "BaseInstructionsContainer.h"
#include "BasePatternInstruction.h"
#include "../SelectedPatterns.h"

namespace Chrysalis {
    class PatternInstructionsContainer: public BaseInstructionsContainer<BasePatternInstruction> {
    public:
        explicit PatternInstructionsContainer(SelectedPatterns* patterns);
        ~PatternInstructionsContainer() override;
    private:
        /// @uml{composition[]}
        SelectedPatterns* patterns_;
    };
}

#endif //CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H