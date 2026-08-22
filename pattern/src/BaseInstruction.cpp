#include "instructions/BaseInstruction.h"

using namespace Chrysalis;

void BaseInstruction::run() {
    if (!executed_) execute();
    executed_ = true;
}

void BaseInstruction::ignore() {
    executed_ = true;
}
