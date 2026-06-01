#ifndef CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H

#include "BaseContainer.h"
#include "BasePatternInstruction.h"

namespace Chrysalis {
    class PatternInstructionsContainer: public BaseContainer<BasePatternInstruction> {
    public:
        explicit PatternInstructionsContainer(PatternSpacesArgument* patternSpaces);
        ~PatternInstructionsContainer() override;

        void execute();
    private:
        /// @uml{composition[]}
        PatternSpacesArgument* patternSpaces_;
    };
}

#endif //CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H