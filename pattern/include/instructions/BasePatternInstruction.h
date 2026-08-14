#ifndef CHRYSALIS_BASEPATTERNINSTRUCTION_H
#define CHRYSALIS_BASEPATTERNINSTRUCTION_H

#include "ProjectSpace.h"
#include "BaseInstruction.h"

#include "arguments/BaseArgument.h"
#include "arguments/PatternsContainerArgument.h"

namespace Chrysalis {
    /**
     * @defgroup Instructions
     * @{
     */
    class BasePatternInstruction: public BaseInstruction {
        SERIALIZED
    public:
        ~BasePatternInstruction() override;
    protected:
        explicit BasePatternInstruction(ProjectSpace* space, args::patterns* patterns);

        [[nodiscard]] ProjectSpace& space() const {
            return *space_;
        }

        ProjectSpace* space_;
        /// @uml{composition}
        args::patterns* patterns_; // TODO: instructions container should own and validate this
    };
};

#endif //CHRYSALIS_BASEPATTERNINSTRUCTION_H