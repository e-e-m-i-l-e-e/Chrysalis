#ifndef CHRYSALIS_PATTERNTRACERENDERER_H
#define CHRYSALIS_PATTERNTRACERENDERER_H

#include "BaseRenderer.h"
#include "MainOpenGLProgram.h"
#include "PatternTraceRendererData.h"

namespace Chrysalis {
    class PatternTraceRenderer: public BaseRenderer<PatternTraceRendererData> {
    public:
        explicit PatternTraceRenderer(MainOpenGLProgram* program, PatternTraceRendererData* rendererData);

        void draw() override;
        void scaleChanged(float scale);

        const Point* pointAtPosition(float x, float y) const;
    private:
        float pointRadius_ = 2.5f;

        MainOpenGLProgram* program_;
    };
}

#endif //CHRYSALIS_PATTERNTRACERENDERER_H