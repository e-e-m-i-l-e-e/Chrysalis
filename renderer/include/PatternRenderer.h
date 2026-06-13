#ifndef CHRYSALIS_PATTERNRENDERER_H
#define CHRYSALIS_PATTERNRENDERER_H

#include "PatternShapeRenderer.h"
#include "PatternSpaceRenderer.h"

namespace Chrysalis {
    class PatternRenderer {
    public:
        explicit PatternRenderer(PatternSpaceRenderer* spaceRenderer, PatternShapeRenderer* shapeRenderer);
        ~PatternRenderer();

        void upload() const;
        void render() const;
        void initialize() const;
        void scaleChanged(float scale) const;
    private:
        /// @uml{composition}
        PatternSpaceRenderer* spaceRenderer_;
        /// @uml{composition}
        PatternShapeRenderer* shapeRenderer_;
    };
}

#endif //CHRYSALIS_PATTERNRENDERER_H