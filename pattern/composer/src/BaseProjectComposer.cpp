#include "projects/BaseProjectComposer.h"

using namespace Chrysalis;

BaseProjectComposer::BaseProjectComposer(Project* project): project_(project) {}

void BaseProjectComposer::fill() {
    fillOptions();
    fillPatterns();
    fillParameters();
    fillInstructions();
}
