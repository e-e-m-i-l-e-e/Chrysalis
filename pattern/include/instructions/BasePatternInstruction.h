#ifndef CHRYSALIS_BASEPATTERNINSTRUCTION_H
#define CHRYSALIS_BASEPATTERNINSTRUCTION_H

#include "ProjectSpace.h"
#include "BaseInstruction.h"

#include "arguments/BaseArgument.h"
#include "arguments/VectorArgument.h"
#include "arguments/PatternsContainerArgument.h"

namespace Chrysalis {
    class BasePatternInstruction: public BaseInstruction {
        SERIALIZED
    public:
        ~BasePatternInstruction() override;
        virtual bool isValid() = 0;
    protected:
        explicit BasePatternInstruction(ProjectSpace* space, args::patterns* patterns);

        [[nodiscard]] ProjectSpace& space() const {
            return *space_;
        }

        ProjectSpace* space_;
        /// @uml{composition}
        args::patterns* patterns_;
    };
};

#endif //CHRYSALIS_BASEPATTERNINSTRUCTION_H