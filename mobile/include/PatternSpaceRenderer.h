#ifndef FASHIONDESIGNAPPS_PATTERNSPACERENDERER_H
#define FASHIONDESIGNAPPS_PATTERNSPACERENDERER_H

#include "SpaceVertex.h"
#include "BaseRenderer.h"
#include "ChrysalisOpenGLProgram.h"
#include "SpaceRendererData.h"

class PatternSpaceRenderer: public BaseRenderer<SpaceVertex> {
public:
    explicit PatternSpaceRenderer(ChrysalisOpenGLProgram* program, const SpaceRendererData* spaceRendererData);

    void draw() override;
    void initialize() override;
    void scaleChanged(float scale);

    std::vector<SpaceVertex> getPoints() const;
private:
    float scale_ = 10.f;

    ChrysalisOpenGLProgram* program_;
    const SpaceRendererData* spaceRendererData_;
};

#endif //FASHIONDESIGNAPPS_PATTERNSPACERENDERER_H