#include "SpaceRendererData.h"

std::vector<SpaceVertex> SpaceRendererData::getVBO() const {
    std::vector<SpaceVertex> vbo;
    vbo.insert(vbo.end(), lines_.begin(), lines_.end());
    vbo.insert(vbo.end(), arrows_.begin(), arrows_.end());
    return vbo;
}

std::vector<int> SpaceRendererData::getIndices() const {
    return vertices_;
}

std::pair<int, int> SpaceRendererData::linesRange() const {
    return {0, lines_.size()};
}

std::pair<int, int> SpaceRendererData::arrowsRange() const {
    return {lines_.size(), lines_.size() + arrows_.size()};
}