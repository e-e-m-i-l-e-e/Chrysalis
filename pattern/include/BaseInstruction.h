#ifndef CHRYSALIS_BASEINSTRUCTION_H
#define CHRYSALIS_BASEINSTRUCTION_H

#include "BaseArgumentObserver.h"

class BaseInstruction: public BaseArgumentObserver {
public:
    virtual bool isValid() = 0;
    virtual void execute() = 0;
};

#endif //CHRYSALIS_BASEINSTRUCTION_H