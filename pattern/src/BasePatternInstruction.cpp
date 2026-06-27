#include "instructions/BasePatternInstruction.h"

using namespace Chrysalis;

BasePatternInstruction::BasePatternInstruction(ProjectSpace* space,
                                               args::patterns* patterns)
    : space_(space), patterns_(patterns) {}

BasePatternInstruction::~BasePatternInstruction() {
    delete patterns_;
}