#ifndef CHRYSALIS_PATTERNSPACERENDERER_H
#define CHRYSALIS_PATTERNSPACERENDERER_H

#include "BaseRenderer.h"
#include "MainOpenGLProgram.h"
#include "PatternSpaceRendererData.h"

namespace Chrysalis {
    class PatternSpaceRenderer: public BaseRenderer<PatternSpaceRendererData> {
    public:
        explicit PatternSpaceRenderer(MainOpenGLProgram* program, PatternSpaceRendererData* rendererData);

        void draw() override;
        void scaleChanged(float scale);

        bool isPointed(float x, float y) const;
    private:
        float pointRadius_ = 2.5f;

        MainOpenGLProgram* program_;
    };
}

#endif //CHRYSALIS_PATTERNSPACERENDERER_H