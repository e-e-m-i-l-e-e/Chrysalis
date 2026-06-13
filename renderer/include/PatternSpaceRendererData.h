#ifndef CHRYSALIS_PATTERNSPACERENDERERDATA_H
#define CHRYSALIS_PATTERNSPACERENDERERDATA_H

#include <vector>

#include "Point.h"
#include "Vertex3f.h"
#include "BaseRendererData.h"

class PatternSpaceRendererData: public BaseRendererData<Vertex3f> {
public:
    void addPoint(const Point* point);

    size_t count() override;
    Vertex3f* vbo() override;
private:
    std::vector<Vertex3f> points_;
};

#endif //CHRYSALIS_PATTERNSPACERENDERERDATA_H