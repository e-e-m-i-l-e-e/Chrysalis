#ifndef CHRYSALIS_CURSORRENDERERDATA_H
#define CHRYSALIS_CURSORRENDERERDATA_H

#include "Vertex3f.h"
#include "BaseRendererData.h"

class CursorRendererData: public BaseRendererData<Vertex3f> {
protected:
    size_t count() override;
public:
    void projectCursor(const Vertex2f& cursor);

    Vertex3f* vbo() override;
private:
    std::vector<Vertex3f> data_;
};

#endif //CHRYSALIS_CURSORRENDERERDATA_H