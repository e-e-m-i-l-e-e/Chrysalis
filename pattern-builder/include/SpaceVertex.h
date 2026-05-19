#ifndef FASHIONDESIGNAPPS_DISTANCEDVERTEX_H
#define FASHIONDESIGNAPPS_DISTANCEDVERTEX_H

#include "Vertex.h"

class SpaceVertex: public Vertex {
public:
    explicit SpaceVertex(float x, float y, float distance);

    float distance() const;

    static std::vector<Layout> getLayout();
private:
    float distance_;
};

#endif //FASHIONDESIGNAPPS_DISTANCEDVERTEX_H