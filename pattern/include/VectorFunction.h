#ifndef CHRYSALIS_VECTORFUNCTIONS_H
#define CHRYSALIS_VECTORFUNCTIONS_H

#include "BaseArgument.h"
#include "Space.h"

class VectorFunction: public BaseArgument {
public:
    explicit VectorFunction(Space* space, const std::string& from, const std::string& to, double(*function)(const VectorFunction*));

    double getValue() const override;

    static double ANGLE(const VectorFunction* function);
    static double LENGTH(const VectorFunction* function);
private:
    Space* space;

    std::string from;
    std::string to;

    double(*function)(const VectorFunction*);
};

#endif //CHRYSALIS_VECTORFUNCTIONS_H