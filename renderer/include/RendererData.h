#ifndef CHRYSALIS_RENDERERDATA_H
#define CHRYSALIS_RENDERERDATA_H

#include <vector>
#include "Vertex3f.h"

class RendererData {
public:
    std::vector<Vertex3f> getVBO() const;
    std::vector<std::pair<int, int>> linesRanges() const;
    std::vector<std::pair<int, int>> arrowsRanges() const;
    std::pair<int, int> pointsRange() const;
    std::vector<Vertex3f> getPoints() const;
};

#endif //CHRYSALIS_RENDERERDATA_H