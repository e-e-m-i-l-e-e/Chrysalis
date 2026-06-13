#include "BaseProject.h"

using namespace Chrysalis;

void BaseProject::fill(Project* project) {
    fillPatterns(project);
    fillParameters(project);
    fillInstructions(project);
}
