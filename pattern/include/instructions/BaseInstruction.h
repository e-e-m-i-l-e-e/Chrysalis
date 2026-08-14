#ifndef CHRYSALIS_BASEINSTRUCTION_H
#define CHRYSALIS_BASEINSTRUCTION_H

#include "serialization.h"

namespace Chrysalis {
    /**
     * @defgroup Instructions
     * @{
     */
    class BaseInstruction {
        SERIALIZED
    protected:
        explicit BaseInstruction() = default;
    public:
        virtual ~BaseInstruction() = default;

        virtual void execute() = 0;
    };
}

#endif //CHRYSALIS_BASEINSTRUCTION_H