#ifndef CHRYSALIS_PATTERNRENDERER_H
#define CHRYSALIS_PATTERNRENDERER_H

#include "PatternShapeRenderer.h"
#include "PatternTraceRenderer.h"

namespace Chrysalis {
    class PatternRenderer {
    public:
        explicit PatternRenderer(std::unique_ptr<PatternTraceRenderer> traceRenderer,
                                 std::unique_ptr<PatternShapeRenderer> shapeRenderer);

        void upload() const;
        void render() const;
        void initialize() const;
        void scaleChanged(float scale) const;

        const PatternTraceRenderer& traceRenderer() const;
    private:
        /// @uml{composition}
        std::unique_ptr<PatternTraceRenderer> traceRenderer_;
        /// @uml{composition}
        std::unique_ptr<PatternShapeRenderer> shapeRenderer_;
    };
}

#endif //CHRYSALIS_PATTERNRENDERER_H