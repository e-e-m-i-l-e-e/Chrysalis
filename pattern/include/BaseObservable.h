#ifndef CHRYSALIS_BASEOBSERVABLE_H
#define CHRYSALIS_BASEOBSERVABLE_H

#include <forward_list>

#include "BaseObserver.h"

class BaseObservable {
public:
    void addObserver(BaseObserver *observer);
protected:
    explicit BaseObservable() = default;

    void valueChanged() const;
private:
    std::forward_list<BaseObserver*> observers_;
};

#endif //CHRYSALIS_BASEOBSERVABLE_H