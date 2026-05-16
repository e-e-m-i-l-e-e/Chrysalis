#ifndef FASHIONDESIGNAPPS_VERTEX_H
#define FASHIONDESIGNAPPS_VERTEX_H

class Vertex {
public:
    explicit Vertex(float x, float y);

    float x() const;
    float y() const;
private:
    float x_;
    float y_;
};

#endif //FASHIONDESIGNAPPS_VERTEX_H