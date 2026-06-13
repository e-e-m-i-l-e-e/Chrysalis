#ifndef CHRYSALIS_CARTESIANRENDERERDATA_H
#define CHRYSALIS_CARTESIANRENDERERDATA_H

#include "Area.h"
#include "Vertex2f.h"
#include "BaseRendererData.h"

namespace Chrysalis {
    class CartesianRendererData: public BaseRendererData<Vertex2f> {
    public:
        size_t count() override;
        Vertex2f* vbo() override;

        void buildGrid(const Area& area, float gridSize);
    private:
        std::vector<Vertex2f> data_;
    };
}

#endif //CHRYSALIS_CARTESIANRENDERERDATA_H