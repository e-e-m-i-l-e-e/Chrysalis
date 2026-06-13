#ifndef CHRYSALIS_CURSORRENDERER_H
#define CHRYSALIS_CURSORRENDERER_H

#include "MainOpenGLProgram.h"
#include "CursorRendererData.h"
#include "BaseAnimatedRenderer.h"

namespace Chrysalis {
    class CursorRenderer: public BaseAnimatedRenderer<CursorRendererData> {
    public:
        explicit CursorRenderer(MainOpenGLProgram* program, CursorRendererData* data);

        void draw() override;
        void hideCursor();
        void displayCursor(const Vertex2f& cursor);
    protected:
        void prepareNextFrame(int64_t startTime, int64_t previousFrameTime, int64_t currentFrameTime) override;
    private:
        float opacity_ = 0.f;
        bool displayCursor_ = false;

        MainOpenGLProgram* program_;
    };
}

#endif //CHRYSALIS_CURSORRENDERER_H