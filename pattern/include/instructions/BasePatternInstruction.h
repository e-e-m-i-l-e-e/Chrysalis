#ifndef CHRYSALIS_BASEPATTERNINSTRUCTION_H
#define CHRYSALIS_BASEPATTERNINSTRUCTION_H

#include "BaseInstruction.h"
#include "../ProjectSpace.h"

#include "../arguments/NameArgument.h"
#include "../arguments/NumberArgument.h"
#include "../arguments/PatternArgument.h"
#include "../arguments/SelectedPatternsArgument.h"

namespace Chrysalis {
    using name = NameArgument;
    using num = NumberArgument;
    using pattern = PatternArgument;

    class BasePatternInstruction: public BaseInstruction {
    public:
        ~BasePatternInstruction() override;
        virtual bool isValid() = 0;
    protected:
        explicit BasePatternInstruction(ProjectSpace* space, SelectedPatternsArgument* selectedPatterns);

        [[nodiscard]] ProjectSpace& space() const {
            return *space_;
        }
        [[nodiscard]] SelectedPatterns& patterns() const {
            return *selectedPatterns_->getArgument();
        }
    private:
        ProjectSpace* space_;
        /// @uml{composition}
        SelectedPatternsArgument* selectedPatterns_;
    };
};

#endif //CHRYSALIS_BASEPATTERNINSTRUCTION_H