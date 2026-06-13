#ifndef CHRYSALIS_PROJECTRENDERER_H
#define CHRYSALIS_PROJECTRENDERER_H

#include "Project.h"
#include "CartesianRenderer.h"
#include "PatternRenderer.h"

namespace Chrysalis {
    class ProjectRenderer {
    public:
        explicit ProjectRenderer(MainOpenGLProgram* program, CartesianRenderer* cartesianRenderer);
        ~ProjectRenderer();

        void initialize() const;

        void areaSizeChanged(float width, float height);
        void areaOffsetChanged(float deltaX, float deltaY);
        void scaleChanged(float scaleFactor, float zoomX, float zoomY);
    protected:
        void useProject(const Project* project);

        void render() const;
        [[nodiscard]] bool prepareNextFrame() const;
    private:
        void updateProjectionMatrix();

        bool isInitialized_ = false;

        Area area_;
        float scale_ = 10.f;

        glm::mat4x4 projection_{};

        /// @uml{composition}
        MainOpenGLProgram* program_;
        /// @uml{composition}
        CartesianRenderer* cartesianRenderer_;
        std::list<PatternRenderer> patternRenderers_;
    };
}

#endif //CHRYSALIS_PROJECTRENDERER_H