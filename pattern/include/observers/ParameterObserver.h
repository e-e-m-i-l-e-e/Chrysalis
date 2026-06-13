#ifndef CHRYSALIS_PARAMETEROBSERVER_H
#define CHRYSALIS_PARAMETEROBSERVER_H

class ParameterObserver {
protected:
    explicit ParameterObserver() = default;
    virtual ~ParameterObserver() = default;
public:
    virtual void valueChanged(double value) = 0;
};

#endif //CHRYSALIS_PARAMETEROBSERVER_H