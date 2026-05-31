#ifndef CHRYSALIS_BASEARGUMENTOBSERVER_H
#define CHRYSALIS_BASEARGUMENTOBSERVER_H

class BaseArgumentObserver {
protected:
    virtual ~BaseArgumentObserver() = default;
public:
    virtual void reset() = 0;
};

#endif //CHRYSALIS_BASEARGUMENTOBSERVER_H