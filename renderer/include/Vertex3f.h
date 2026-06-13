#ifndef CHRYSALIS_VERTEX3F_H
#define CHRYSALIS_VERTEX3F_H

#include "Vertex2f.h"

namespace Chrysalis {
    class Vertex3f: public Vertex2f {
    public:
        explicit Vertex3f(float x, float y, float attribute);
    private:
        float attribute;
    };
}

#endif //CHRYSALIS_VERTEX3F_H