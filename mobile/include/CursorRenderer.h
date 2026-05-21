#ifndef FASHIONDESIGNAPPS_CURSORRENDERER_H
#define FASHIONDESIGNAPPS_CURSORRENDERER_H

#include <QPointF>

#include "SpaceVertex.h"
#include "BaseRenderer.h"
#include "ChrysalisOpenGLProgram.h"

class CursorRenderer: public BaseRenderer<SpaceVertex> {
public:
    explicit CursorRenderer(ChrysalisOpenGLProgram* program);

    void render() override;
    void changeCursor(const QPointF& cursor);
private:
    QPointF cursor_;

    ChrysalisOpenGLProgram* program_;
};

#endif //FASHIONDESIGNAPPS_CURSORRENDERER_H