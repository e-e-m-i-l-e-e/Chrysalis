#ifndef CHRYSALIS_BINARYFUNCTION_H
#define CHRYSALIS_BINARYFUNCTION_H

#include "BaseArgument.h"

class BinaryFunction: public BaseArgument {
public:
    explicit BinaryFunction(BaseArgument* argumentLeft,
                            BaseArgument* argumentRight,
                            double (*function)(double a, double b));

    double getValue() const override;

    static double ADDITION(double a, double b);
    static double SUBTRACTION(double a, double b);
    static double MULTIPLICATION(double a, double b);
    static double DIVISION(double a, double b);

    static double MIN(double a, double b);
    static double MAX(double a, double b);
private:
    BaseArgument* argumentLeft;
    BaseArgument* argumentRight;
    double(*function)(double a, double b);
};

#endif //CHRYSALIS_BINARYFUNCTION_H