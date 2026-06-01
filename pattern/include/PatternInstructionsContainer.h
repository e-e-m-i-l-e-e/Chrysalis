#ifndef CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H

#include "BaseContainer.h"
#include "BasePatternInstruction.h"
#include "SelectedPatterns.h"

namespace Chrysalis {
    class PatternInstructionsContainer: public BaseContainer<BasePatternInstruction> {
    public:
        explicit PatternInstructionsContainer(SelectedPatterns* patterns);
        ~PatternInstructionsContainer() override;

        void execute() const;
    private:
        /// @uml{composition[]}
        SelectedPatterns* patterns_;
    };
}

#endif //CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H