#ifndef CHRYSALIS_CURSORRENDERER_H
#define CHRYSALIS_CURSORRENDERER_H

#include "Vertex3f.h"
#include "BaseAnimatedRenderer.h"
#include "CursorRendererData.h"
#include "MainOpenGLProgram.h"

class CursorRenderer: public BaseAnimatedRenderer<CursorRendererData> {
public:
    explicit CursorRenderer(Chrysalis::MainOpenGLProgram* program, CursorRendererData* data);

    void draw() override;
    void hideCursor();
    void displayCursor(const Vertex2f& cursor);
protected:
    void prepareNextFrame(int64_t startTime, int64_t previousFrameTime, int64_t currentFrameTime) override;
private:
    float opacity_ = 0.f;
    bool displayCursor_ = false;

    Chrysalis::MainOpenGLProgram* program_;
};

#endif //CHRYSALIS_CURSORRENDERER_H