#ifndef FASHIONDESIGNAPPS_SPACERENDERERDATA_H
#define FASHIONDESIGNAPPS_SPACERENDERERDATA_H

#include <vector>

#include "SpaceVertex.h"

class SpaceRendererData {
public:
    std::vector<SpaceVertex> getVBO() const;
    std::vector<int> getIndices() const;

    std::pair<int, int> linesRange() const;
    std::pair<int, int> arrowsRange() const;
private:
    std::vector<int> vertices_;
    std::vector<SpaceVertex> lines_;
    std::vector<SpaceVertex> arrows_;
};

#endif //FASHIONDESIGNAPPS_SPACERENDERERDATA_H