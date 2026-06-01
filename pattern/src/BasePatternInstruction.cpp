#include "BasePatternInstruction.h"

#include "PatternSpacesArgument.h"

using namespace Chrysalis;

BasePatternInstruction::BasePatternInstruction(ProjectSpace* space,
                                                           Argument<PatternSpacesArgument*>* patternSpaces)
    : space_(space), patternSpaces_(patternSpaces) {}

BasePatternInstruction::~BasePatternInstruction() {
    delete patternSpaces_;
}
