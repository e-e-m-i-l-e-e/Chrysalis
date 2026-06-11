#include "ProjectRenderer.h"

using namespace Chrysalis;

ProjectRenderer::ProjectRenderer(Project* project_, CartesianRenderer* cartesianRenderer)
    : cartesianRenderer_(cartesianRenderer)
{}

ProjectRenderer::~ProjectRenderer() {
    delete cartesianRenderer_;
}
