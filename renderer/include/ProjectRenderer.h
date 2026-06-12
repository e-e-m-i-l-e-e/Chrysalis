#ifndef CHRYSALIS_PROJECTRENDERER_H
#define CHRYSALIS_PROJECTRENDERER_H

#include "Project.h"
#include "CartesianRenderer.h"

namespace Chrysalis {
    class ProjectRenderer {
    public:
        explicit ProjectRenderer(Project* project, MainOpenGLProgram* program, CartesianRenderer* cartesianRenderer);
        ~ProjectRenderer();

        void initialize() const;
        void render() const;
        bool prepareNextFrame() const;

        void areaSizeChanged(float width, float height);
        void areaOffsetChanged(float deltaX, float deltaY);

        void scaleChanged(float scaleFactor, float zoomX, float zoomY);
    private:
        void updateProjectionMatrix();

        Area area_;
        float scale_ = 10.f;

        glm::mat4x4 projection_;

        /// @uml{composition}
        MainOpenGLProgram* program_;
        /// @uml{composition}
        CartesianRenderer* cartesianRenderer_;
    };
}

#endif //CHRYSALIS_PROJECTRENDERER_H