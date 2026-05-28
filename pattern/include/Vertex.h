#ifndef FASHIONDESIGNAPPS_VERTEX_H
#define FASHIONDESIGNAPPS_VERTEX_H

#include <vector>

class Vertex {
public:
    struct Layout {
        int size;
        void* offset;
    };
    explicit Vertex(float x, float y);

    float x() const;
    float y() const;

    static std::vector<Layout> getLayout();
private:
    float x_;
    float y_;
};

#endif //FASHIONDESIGNAPPS_VERTEX_H