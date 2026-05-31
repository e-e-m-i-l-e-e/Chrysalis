#ifndef CHRYSALIS_BASEARGUMENT_H
#define CHRYSALIS_BASEARGUMENT_H

#include <forward_list>
#include <boost/optional/optional.hpp>

#include "BaseArgumentObserver.h"

template<typename T>
class Argument {
public:
    explicit Argument() = default;
    explicit Argument(T argument): argument_(argument) {}
    virtual ~Argument() = default;

    bool hasArgument() {
        return argument_.has_value();
    }
    void setArgument(T value) {
        argument_ = value;
        argumentChanged();
    }
    void resetArgument() {
        argument_.reset();
    }
    [[nodiscard]] const T& getArgument() const {
        return argument_.value();
    }

    void addObserver(BaseArgumentObserver* observer) {
        observers_.push_front(observer);
    }
protected:
    void argumentChanged() const {
        for (const auto& observer: observers_) {
            observer->reset();
        }
    }

    boost::optional<T> argument_;
private:
    std::forward_list<BaseArgumentObserver*> observers_;
};

#endif //CHRYSALIS_BASEARGUMENT_H