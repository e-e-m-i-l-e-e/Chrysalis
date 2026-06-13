#ifndef CHRYSALIS_VERTEX2F_H
#define CHRYSALIS_VERTEX2F_H

#include <vector>

namespace Chrysalis {
    class Vertex2f {
    public:
        explicit Vertex2f(float x, float y);

        const float& x() const;
        const float& y() const;

        static std::vector<std::pair<int, void*>> getLayout();
    private:
        const float x_;
        const float y_;
    };
}

#endif //CHRYSALIS_VERTEX2F_H