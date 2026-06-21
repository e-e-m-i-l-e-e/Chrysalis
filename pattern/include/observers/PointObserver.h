#ifndef CHRYSALIS_POINTOBSERVER_H
#define CHRYSALIS_POINTOBSERVER_H

#include "BaseObserver.h"

namespace Chrysalis {
    class Point;

    class PointObserver: public BaseObserver<PointObserver> {
    protected:
        explicit PointObserver() = default;
    public:
        virtual void pointMoved(const Point* point) = 0;
    };
}

#endif //CHRYSALIS_POINTOBSERVER_H