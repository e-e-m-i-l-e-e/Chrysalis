#include "initializers/Instructions.h"

using namespace Chrysalis::Composer;

Instructions::Instructions(const Project* project) {
    space = project->getSpace();
    outerInstructionsContainer_ = instructionsContainer;
    instructionsContainer = project->getInstructions();
}

Instructions::~Instructions() {
    instructionsContainer = outerInstructionsContainer_;
}

void Instructions::operator<<(const std::initializer_list<BaseInstruction*>& instructions) const {
    for (const auto& instruction : instructions) {
        instructionsContainer->add(instruction);
    }
}
