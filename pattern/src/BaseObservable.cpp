#include "BaseObservable.h"

void BaseObservable::addObserver(BaseObserver* observer) {
    observers_.push_front(observer);
}

void BaseObservable::valueChanged() const {
    for (BaseObserver* observer : observers_) {
        observer->valueChanged();
    }
}