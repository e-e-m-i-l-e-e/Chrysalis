#ifndef CHRYSALIS_BASEOBSERVER_H
#define CHRYSALIS_BASEOBSERVER_H

#include "BaseObservable.h"

namespace Chrysalis {
    /**
     * @defgroup Observers
     * @{
     */
    template <typename T>
    class BaseObserver {
    protected:
        explicit BaseObserver() = default;
        virtual ~BaseObserver() = default;

        void observe(const BaseObservable<T>* observable) {
            const_cast<BaseObservable<T>*>(observable)->addObserver(dynamic_cast<T*>(this));
        }
    };
}

#endif //CHRYSALIS_BASEOBSERVER_H