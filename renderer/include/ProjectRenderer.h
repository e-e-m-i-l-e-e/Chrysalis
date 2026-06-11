#ifndef CHRYSALIS_PROJECTRENDERER_H
#define CHRYSALIS_PROJECTRENDERER_H

#include "Project.h"
#include "CartesianRenderer.h"

namespace Chrysalis {
    class ProjectRenderer {
    public:
        explicit ProjectRenderer(Project* project_, CartesianRenderer* cartesianRenderer);
        ~ProjectRenderer();
    private:
        /// @uml{composition}
        CartesianRenderer* cartesianRenderer_;
    };
}

#endif //CHRYSALIS_PROJECTRENDERER_H