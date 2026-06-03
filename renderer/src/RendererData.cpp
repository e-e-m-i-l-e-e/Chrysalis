#include "RendererData.h"

std::vector<Vertex3f> RendererData::getVBO() const
{
    return {};
}

std::vector<std::pair<int, int>> RendererData::linesRanges() const
{
    return {};
}

std::vector<std::pair<int, int>> RendererData::arrowsRanges() const
{
    return {};
}

std::pair<int, int> RendererData::pointsRange() const
{
    return {};
}

std::vector<Vertex3f> RendererData::getPoints() const
{
    return {};
}
