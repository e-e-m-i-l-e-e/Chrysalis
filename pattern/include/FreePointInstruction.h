#ifndef CHRYSALIS_FREEPOINTINSTRUCTION_H
#define CHRYSALIS_FREEPOINTINSTRUCTION_H

#include "BaseInstruction.h"

/**
 * \uml{note[top] Syntax samples:
 * A (1, 1)
 * "A 1" (1.0, 2)
 * A (exp() exp())}
 */
class FreePointInstruction: public BaseInstruction {
public:
    void reset() override;
    void execute() override;
};

#endif //CHRYSALIS_FREEPOINTINSTRUCTION_H