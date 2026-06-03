#ifndef CHRYSALIS_AREA_H
#define CHRYSALIS_AREA_H

class Area {
public:
    explicit Area(float x, float y, float width, float height): x_(x), y_(y), width_(width), height_(height) {}

    const float& x() const
    {
        return x_;
    }
    const float& y() const
    {
        return y_;
    }
    const float& width() const {
        return width_;
    }
    const float& height() const
    {
        return height_;
    }
private:
    float x_;
    float y_;
    float width_;
    float height_;
};

#endif //CHRYSALIS_AREA_H