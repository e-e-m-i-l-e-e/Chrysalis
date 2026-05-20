#ifndef FASHIONDESIGNAPPS_BASERENDERER_H
#define FASHIONDESIGNAPPS_BASERENDERER_H

class BaseRenderer {
protected:
    virtual ~BaseRenderer() = default;
public:
    virtual void draw() = 0;
};

#endif //FASHIONDESIGNAPPS_BASERENDERER_H