#include "BaseProjectComposer.h"

using namespace Chrysalis;

void BaseProjectComposer::fill(Project* project) {
    fillPatterns(project);
    fillParameters(project);
    fillInstructions(project);
}
