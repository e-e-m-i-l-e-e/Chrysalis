#ifndef CHRYSALIS_PATTERNSHAPERENDERERDATA_H
#define CHRYSALIS_PATTERNSHAPERENDERERDATA_H

#include "BaseRendererData.h"

namespace Chrysalis {
    class PatternShapeRendererData: public BaseRendererData<Vertex2f> {
    public:
        size_t size() override;
        std::vector<Vertex2f> vbo() override;
    };
}

#endif //CHRYSALIS_PATTERNSHAPERENDERERDATA_H