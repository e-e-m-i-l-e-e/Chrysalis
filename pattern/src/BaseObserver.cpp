#include "BaseObserver.h"

#include "BaseObservable.h"

void BaseObserver::observe(BaseObservable* observable) {
    observable->addObserver(this);
}
