#ifndef CHRYSALIS_PATTERNRENDERER_H
#define CHRYSALIS_PATTERNRENDERER_H

#include "PatternShapeRenderer.h"
#include "PatternTraceRenderer.h"

namespace Chrysalis {
    class PatternRenderer {
    public:
        explicit PatternRenderer(PatternTraceRenderer* traceRenderer, PatternShapeRenderer* shapeRenderer);
        ~PatternRenderer();

        void upload() const;
        void render() const;
        void initialize() const;
        void scaleChanged(float scale) const;

        const PatternTraceRenderer* traceRenderer() const;
    private:
        /// @uml{composition}
        PatternTraceRenderer* traceRenderer_;
        /// @uml{composition}
        PatternShapeRenderer* shapeRenderer_;
    };
}

#endif //CHRYSALIS_PATTERNRENDERER_H