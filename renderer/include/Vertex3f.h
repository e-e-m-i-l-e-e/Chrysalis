#ifndef CHRYSALIS_VERTEX3F_H
#define CHRYSALIS_VERTEX3F_H

#include "Vertex2f.h"

namespace Chrysalis {
    class Vertex3f: public Vertex2f {
    public:
        explicit Vertex3f(const Point& point);
        explicit Vertex3f(const Point& point, float attribute);

        explicit Vertex3f(float x, float y);
        explicit Vertex3f(float x, float y, float attribute);

        void attribute(float value);
        const float& attribute() const;

        static std::vector<std::pair<int, void*>> layout();
    private:
        float attribute_;
    };
}

#endif //CHRYSALIS_VERTEX3F_H