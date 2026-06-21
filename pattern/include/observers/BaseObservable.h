#ifndef CHRYSALIS_BASEOBSERVABLE_H
#define CHRYSALIS_BASEOBSERVABLE_H

#include <forward_list>

template<typename T>
class BaseObservable {
protected:
    explicit BaseObservable() = default;
public:
    template<typename... Args, typename... CallArgs>
    void notify(void(T::*function)(Args...), CallArgs&&... args) {
        for (const auto& observer: observers_) {
            (observer->*function)(std::forward<CallArgs>(args)...);
        }
    }
    void addObserver(T* observer) {
        observers_.push_front(observer);
    }
private:
    std::forward_list<T*> observers_;
};

#endif //CHRYSALIS_BASEOBSERVABLE_H