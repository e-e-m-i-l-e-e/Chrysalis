#ifndef CHRYSALIS_CURSORRENDERER_H
#define CHRYSALIS_CURSORRENDERER_H

#include "SpaceVertex.h"
#include "BaseAnimatedRenderer.h"
#include "ChrysalisOpenGLProgram.h"

class CursorRenderer: public BaseAnimatedRenderer<SpaceVertex> {
public:
    explicit CursorRenderer(ChrysalisOpenGLProgram* program);

    void draw() override;
    void hideCursor();
    void displayCursor(const QPointF& cursor);
protected:
    void prepareNextFrame(qint64 startTime, qint64 previousFrameTime, qint64 currentFrameTime) override;
private:
    float opacity_ = 0.f;
    bool displayCursor_ = false;

    ChrysalisOpenGLProgram* program_;
};

#endif //CHRYSALIS_CURSORRENDERER_H