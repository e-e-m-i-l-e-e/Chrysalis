#ifndef CHRYSALIS_BASEOBSERVABLERENDERERDATA_H
#define CHRYSALIS_BASEOBSERVABLERENDERERDATA_H

#include "BaseRendererData.h"
#include "BaseRendererObserver.h"

namespace Chrysalis {
    template<typename T>
    class BaseObservableRendererData: public BaseRendererData<T> {
    protected:
        explicit BaseObservableRendererData(const std::vector<BaseRendererObserver*>& observers): observers_(observers) {}
    public:
        void updateVBO() override {
            BaseRendererData<T>::updateVBO();
            for (const auto observer: observers_) {
                observer->vboChanged();
            }
        }
    private:
        const std::vector<BaseRendererObserver*>& observers_;
    };
}

#endif // CHRYSALIS_BASEOBSERVABLERENDERERDATA_H
