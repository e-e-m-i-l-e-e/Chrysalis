#include "BaseProjectComposer.h"

using namespace Chrysalis;

BaseProjectComposer::BaseProjectComposer(Project* project): project_(project) {}

void BaseProjectComposer::fill() {
    fillPatterns();
    fillParameters();
    fillInstructions();
}
