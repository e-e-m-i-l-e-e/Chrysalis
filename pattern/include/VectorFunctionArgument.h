#ifndef CHRYSALIS_VECTORFUNCTIONS_H
#define CHRYSALIS_VECTORFUNCTIONS_H

#include "Space.h"
#include "Argument.h"

class VectorFunctionArgument: public Argument<double> {
public:
    struct Use {
        static double ANGLE(const VectorFunctionArgument* function);
        static double LENGTH(const VectorFunctionArgument* function);
    };
    explicit VectorFunctionArgument(Space* space, std::string  from, std::string  to, double(*function)(const VectorFunctionArgument*));
private:
    Space* space;

    std::string from;
    std::string to;

    double(*function)(const VectorFunctionArgument*);
};

#endif //CHRYSALIS_VECTORFUNCTIONS_H