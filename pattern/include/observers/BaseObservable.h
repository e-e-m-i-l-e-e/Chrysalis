#ifndef CHRYSALIS_BASEOBSERVABLE_H
#define CHRYSALIS_BASEOBSERVABLE_H

#include <set>
#include <mutex>

/**
 * @defgroup Observers Observers
 * @{
 */
namespace Chrysalis {
    template<typename T>
    class BaseObservable {
    protected:
        explicit BaseObservable() = default;
        virtual ~BaseObservable() = default;
    public:
        template<typename... Args, typename... CallArgs>
        void notify(void(T::*function)(Args...), CallArgs&&... args) const {
            std::lock_guard lock(mutex_);
            for (const auto& observer: observers_) {
                (observer->*function)(std::forward<CallArgs>(args)...);
            }
        }
        void addObserver(T* observer) {
            std::lock_guard lock(mutex_);
            observers_.insert(observer);
        }
        void removeObserver(T* observer) {
            std::lock_guard lock(mutex_);
            observers_.erase(observer);
        }
    private:
        std::set<T*> observers_;
        mutable std::mutex mutex_;
    };
}
/**@}*/

#endif //CHRYSALIS_BASEOBSERVABLE_H