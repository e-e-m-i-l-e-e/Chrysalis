#ifndef CHRYSALIS_CURSORRENDERERDATA_H
#define CHRYSALIS_CURSORRENDERERDATA_H

#include "Vertex3f.h"
#include "BaseRendererData.h"

namespace Chrysalis {
    class CursorRendererData: public BaseRendererData<Vertex3f> {
    public:
        void projectCursor(const Vertex2f& cursor);

        size_t count() override;
        Vertex3f* vbo() override;
    private:
        std::vector<Vertex3f> data_;
    };
}

#endif //CHRYSALIS_CURSORRENDERERDATA_H