#include "BasePatternInstruction.h"

#include "arguments/SelectedPatternsArgument.h"

using namespace Chrysalis;

BasePatternInstruction::BasePatternInstruction(ProjectSpace* space,
                                               SelectedPatternsArgument* selectedPatterns)
    : space_(space), selectedPatterns_(selectedPatterns) {}

BasePatternInstruction::~BasePatternInstruction() {
    delete selectedPatterns_;
}
