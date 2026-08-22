#ifndef CHRYSALIS_BASEINSTRUCTION_H
#define CHRYSALIS_BASEINSTRUCTION_H

#include "serialization.h"

/** @defgroup Instructions Instructions
 *  @{
 */
namespace Chrysalis {
    class BaseInstruction {
        SERIALIZED
    protected:
        explicit BaseInstruction() = default;
    public:
        virtual ~BaseInstruction() = default;

        void run();
        virtual void ignore();
    protected:
        virtual void execute() = 0;

        bool executed_ = false;
    };
}
/**@}*/

#endif //CHRYSALIS_BASEINSTRUCTION_H