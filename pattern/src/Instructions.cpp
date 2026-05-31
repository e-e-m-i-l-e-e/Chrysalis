#include "Instructions.h"

Instructions::~Instructions() {
    for (const auto& instruction: instructions) delete instruction;
}

void Instructions::addInstruction(BaseInstruction* instruction) {
    instructions.push_back(instruction);
    instruction->execute();
}
