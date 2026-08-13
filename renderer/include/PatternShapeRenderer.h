#ifndef CHRYSALIS_PATTERNSHAPERENDERER_H
#define CHRYSALIS_PATTERNSHAPERENDERER_H

#include "BaseRenderer.h"
#include "MainOpenGLProgram.h"
#include "PatternShapeRendererData.h"

namespace Chrysalis {
    class PatternShapeRenderer: public BaseRenderer<PatternShapeRendererData> {
    public:
        explicit PatternShapeRenderer(MainOpenGLProgram* program, PatternShapeRendererData* data);

        void draw() override;
    private:
        MainOpenGLProgram* program_;
    };
}

#endif //CHRYSALIS_PATTERNSHAPERENDERER_H