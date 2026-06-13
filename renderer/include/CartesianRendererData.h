#ifndef CHRYSALIS_CARTESIANRENDERERDATA_H
#define CHRYSALIS_CARTESIANRENDERERDATA_H

#include "Area.h"
#include "Vertex2f.h"
#include "BaseRendererData.h"

class CartesianRendererData: public BaseRendererData<Vertex2f> {
public:
    void buildGrid(const Chrysalis::Area& area, float gridSize);

    size_t count() override;
    Vertex2f* vbo() override;
private:
    std::vector<Vertex2f> data_;
};

#endif //CHRYSALIS_CARTESIANRENDERERDATA_H