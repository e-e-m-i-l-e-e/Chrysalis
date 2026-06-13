#ifndef CHRYSALIS_PATTERNSHAPERENDERERDATA_H
#define CHRYSALIS_PATTERNSHAPERENDERERDATA_H

#include "BaseRendererData.h"

class PatternShapeRendererData: public BaseRendererData<Vertex2f> {
protected:
    size_t count() override;
public:
    Vertex2f* vbo() override;
};

#endif //CHRYSALIS_PATTERNSHAPERENDERERDATA_H