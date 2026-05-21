#ifndef FASHIONDESIGNAPPS_CURSORRENDERER_H
#define FASHIONDESIGNAPPS_CURSORRENDERER_H

#include "BaseRenderer.h"

class CursorRenderer: public BaseRenderer<Vertex> {
public:
    void render() override;
};

#endif //FASHIONDESIGNAPPS_CURSORRENDERER_H