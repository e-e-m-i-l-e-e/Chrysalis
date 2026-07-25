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

void Instructions::operator<<(std::initializer_list<std::vector<BaseInstruction*>>&& instructionBlocks) const {
    for (const auto& instructions : instructionBlocks) {
        for (const auto& instruction : instructions) {
            instructionsContainer->add(instruction);
        }
    }
}
