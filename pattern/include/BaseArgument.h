#ifndef CHRYSALIS_BASEARGUMENT_H
#define CHRYSALIS_BASEARGUMENT_H

class BaseArgument {
protected:
    explicit BaseArgument() = default;
public:
    virtual ~BaseArgument() = default;

    virtual double getValue() const = 0;
};

#endif //CHRYSALIS_BASEARGUMENT_H