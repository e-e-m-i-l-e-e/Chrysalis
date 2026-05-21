#ifndef FASHIONDESIGNAPPS_PATTERNSHAPERENDERER_H
#define FASHIONDESIGNAPPS_PATTERNSHAPERENDERER_H

#include "BaseRenderer.h"

class PatternShapeRenderer: public BaseRenderer<Vertex> {
public:
    void render() override;
    void scaleChanged(float scale);
};

#endif //FASHIONDESIGNAPPS_PATTERNSHAPERENDERER_H