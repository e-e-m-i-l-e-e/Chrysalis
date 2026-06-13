#ifndef CHRYSALIS_PATTERNSHAPERENDERER_H
#define CHRYSALIS_PATTERNSHAPERENDERER_H

#include "BaseRenderer.h"
#include "PatternShapeRendererData.h"

namespace Chrysalis {
    class PatternShapeRenderer: public BaseRenderer<PatternShapeRendererData> {
    public:
        explicit PatternShapeRenderer(PatternShapeRendererData* data);

        void draw() override;
        void scaleChanged(float scale);
    };
}

#endif //CHRYSALIS_PATTERNSHAPERENDERER_H