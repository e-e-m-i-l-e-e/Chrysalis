#ifndef CHRYSALIS_PATTERNSPACERENDERER_H
#define CHRYSALIS_PATTERNSPACERENDERER_H

#include "Vertex3f.h"
#include "BaseRenderer.h"
#include "MainOpenGLProgram.h"
#include "RendererData.h"

class PatternSpaceRenderer: public BaseRenderer<Vertex3f> {
public:
    explicit PatternSpaceRenderer(Chrysalis::MainOpenGLProgram* program, const RendererData* spaceRendererData);

    void draw() override;
    void initialize() override;
    void scaleChanged(float scale);
private:
    float pointRadius_ = 2.5f;

    Chrysalis::MainOpenGLProgram* program_;
    const RendererData* spaceRendererData_;
};

#endif //CHRYSALIS_PATTERNSPACERENDERER_H