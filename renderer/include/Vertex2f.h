#ifndef CHRYSALIS_VERTEX2F_H
#define CHRYSALIS_VERTEX2F_H

#include <vector>

#include "Point.h"
#include "Transformation.h"

namespace Chrysalis {
    class Vertex2f {
    public:
        explicit Vertex2f(float x, float y);
        explicit Vertex2f(const Point& point);

        const float& x() const;
        const float& y() const;

        void move(const Point& point);
        void transform(const Transformation& transformation);

        static std::vector<std::pair<int, void*>> layout();
    private:
        float x_;
        float y_;
    };
}

#endif //CHRYSALIS_VERTEX2F_H