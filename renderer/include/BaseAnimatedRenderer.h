#ifndef CHRYSALIS_BASEANIMATEDRENDERER_H
#define CHRYSALIS_BASEANIMATEDRENDERER_H

#include <chrono>

#include "BaseRenderer.h"

namespace Chrysalis {
    template<typename D>
    class BaseAnimatedRenderer: public BaseRenderer<D> {
    protected:
        explicit BaseAnimatedRenderer(D* data): BaseRenderer<D>(data) {}

        void complete() {
            isCompleted_ = true;
        }
        virtual void prepareNextFrame(int64_t startTime, int64_t previousFrameTime, int64_t currentFrameTime) = 0;
    public:
        bool animate() {
            const auto now = clock::now();
            const int64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

            if (isCompleted_) {
                startTime_ = currentTime;
                isCompleted_ = false;
                time_ = currentTime;
            }
            prepareNextFrame(startTime_, time_, currentTime);
            time_ = currentTime;
            BaseRenderer<D>::upload();
            return !isCompleted_;
        }
    private:
        using clock = std::chrono::steady_clock;

        int64_t time_ = 0;
        int64_t startTime_ = 0;
        bool isCompleted_ = true;
    };
}

#endif //CHRYSALIS_BASEANIMATEDRENDERER_H