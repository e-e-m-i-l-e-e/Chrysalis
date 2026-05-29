#ifndef FASHIONDESIGNAPPS_PATTERNRENDERER_H
#define FASHIONDESIGNAPPS_PATTERNRENDERER_H

#include "PatternShapeRenderer.h"
#include "PatternSpaceRenderer.h"

class PatternRenderer {
public:
    explicit PatternRenderer(PatternSpaceRenderer* spaceRenderer, PatternShapeRenderer* shapeRenderer);

    void render() const;
    void initialize() const;
    void scaleChanged(float scale) const;

    std::vector<SpaceVertex> getPoints() const;
private:
    PatternSpaceRenderer* spaceRenderer_;
    PatternShapeRenderer* shapeRenderer_;
};

#endif //FASHIONDESIGNAPPS_PATTERNRENDERER_H