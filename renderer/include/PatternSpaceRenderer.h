#ifndef CHRYSALIS_PATTERNSPACERENDERER_H
#define CHRYSALIS_PATTERNSPACERENDERER_H

#include "BaseRenderer.h"
#include "MainOpenGLProgram.h"
#include "PatternSpaceRendererData.h"
#include "observers/PatternSpaceObserver.h"

namespace Chrysalis {
    class PatternSpaceRenderer: public BaseRenderer<PatternSpaceRendererData>, public PatternSpaceObserver {
    public:
        explicit PatternSpaceRenderer(MainOpenGLProgram* program, PatternSpaceRendererData* rendererData);

        void draw() override;
        void scaleChanged(float scale);

        void pointAdded(const Point* point) override;
        void relativePointAdded(const Point* from, const Point* to) override;
    private:
        float pointRadius_ = 2.5f;

        MainOpenGLProgram* program_;
    };
}

#endif //CHRYSALIS_PATTERNSPACERENDERER_H