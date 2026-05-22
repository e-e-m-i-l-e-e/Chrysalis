#ifndef FASHIONDESIGNAPPS_BASEARGUMENT_H
#define FASHIONDESIGNAPPS_BASEARGUMENT_H

class BaseArgument {
protected:
    explicit BaseArgument() = default;
public:
    virtual ~BaseArgument() = default;

    virtual double getValue() const = 0;
};

#endif //FASHIONDESIGNAPPS_BASEARGUMENT_H