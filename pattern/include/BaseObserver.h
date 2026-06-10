#ifndef CHRYSALIS_BASEOBSERVER_H
#define CHRYSALIS_BASEOBSERVER_H

class BaseObservable;

class BaseObserver {
protected:
    explicit BaseObserver() = default;
public:
    virtual ~BaseObserver() = default;

    void observe(BaseObservable *observable);
    virtual void valueChanged() = 0;
};

#endif //CHRYSALIS_BASEOBSERVER_H