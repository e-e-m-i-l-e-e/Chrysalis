#include "BasePatternSpacesInstruction.h"

#include "PatternSpacesArgument.h"

using namespace Chrysalis;

BasePatternSpacesInstruction::BasePatternSpacesInstruction(ProjectSpace* space,
                                                           Argument<PatternSpacesArgument*>* patternSpaces)
    : space_(space), patternSpaces_(patternSpaces) {
    patternSpaces_->addObserver(this);
}

BasePatternSpacesInstruction::~BasePatternSpacesInstruction() {
    delete patternSpaces_;
}
