#ifndef FASHIONDESIGNAPPS_DISTANCEDVERTEX_H
#define FASHIONDESIGNAPPS_DISTANCEDVERTEX_H

#include "Vertex.h"

class DistancedVertex: public Vertex {
public:
    explicit DistancedVertex(float x, float y, float distance);

    float distance() const;
private:
    float distance_;
};

#endif //FASHIONDESIGNAPPS_DISTANCEDVERTEX_H