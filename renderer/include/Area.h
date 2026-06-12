#ifndef CHRYSALIS_AREA_H
#define CHRYSALIS_AREA_H

namespace Chrysalis {
    class Area {
    public:
        explicit Area();
        explicit Area(float x, float y, float width, float height);

        [[nodiscard]] const float& x() const;
        [[nodiscard]] const float& y() const;
        [[nodiscard]] const float& width() const;
        [[nodiscard]] const float& height() const;

        void scale(float scaleFactor);
        void offset(float deltaX, float deltaY);
        void setSize(float width, float height);
    private:
        float x_;
        float y_;
        float width_;
        float height_;
    };
}

#endif //CHRYSALIS_AREA_H