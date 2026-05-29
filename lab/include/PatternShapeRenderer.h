#ifndef CHRYSALIS_PATTERNSHAPERENDERER_H
#define CHRYSALIS_PATTERNSHAPERENDERER_H

#include "BaseRenderer.h"

class PatternShapeRenderer: public BaseRenderer<Vertex> {
public:
    void draw() override;
    void scaleChanged(float scale);
};

#endif //CHRYSALIS_PATTERNSHAPERENDERER_H