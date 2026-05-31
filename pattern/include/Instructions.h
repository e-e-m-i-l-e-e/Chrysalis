#ifndef CHRYSALIS_INSTRUCTIONS_H
#define CHRYSALIS_INSTRUCTIONS_H

#include <list>

#include "serialization.h"
#include "BaseInstruction.h"

class SERIALIZABLE(Instructions) {
public:
    ~Instructions();

    void addInstruction(BaseInstruction* instruction);
private:
    std::list<BaseInstruction*> instructions;
};

DEFAULT_SERIALIZE_MEMBERS(Instructions)

#endif //CHRYSALIS_INSTRUCTIONS_H