#ifndef CHRYSALIS_BASEANIMATEDRENDERER_H
#define CHRYSALIS_BASEANIMATEDRENDERER_H

#include <iostream>
#include <QElapsedTimer>

#include "BaseRenderer.h"

template<typename V>
class BaseAnimatedRenderer: public BaseRenderer<V> {
protected:
    explicit BaseAnimatedRenderer() = default;

    void complete() {
        isCompleted_ = true;
    }
    virtual void prepareNextFrame(qint64 startTime, qint64 previousFrameTime, qint64 currentFrameTime) = 0;
private:
    using BaseRenderer<V>::upload;
public:
    bool animate() {
        const qint64 currentTime = timer_.elapsed();
        if (isCompleted_) {
            startTime_ = timer_.elapsed();
            isCompleted_ = false;
            time_ = currentTime;
        }
        prepareNextFrame(startTime_, time_, currentTime);
        time_ = currentTime;
        BaseRenderer<V>::upload();
        return !isCompleted_;
    }
private:
    qint64 time_ {};
    qint64 startTime_ {};
    bool isCompleted_ = true;

    QElapsedTimer timer_;
};

#endif //CHRYSALIS_BASEANIMATEDRENDERER_H