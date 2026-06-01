#ifndef CHRYSALIS_BINARYFUNCTION_H
#define CHRYSALIS_BINARYFUNCTION_H

#include "Argument.h"
#include "NumberArgument.h"

class BinaryFunctionArgument: public NumberArgument {
public:
    struct Use {
        static double ADDITION(double a, double b);
        static double SUBTRACTION(double a, double b);
        static double MULTIPLICATION(double a, double b);
        static double DIVISION(double a, double b);

        static double MIN(double a, double b);
        static double MAX(double a, double b);
    };
    explicit BinaryFunctionArgument(Argument* argumentLeft,
                            Argument* argumentRight,
                            double (*function)(double a, double b));
    ~BinaryFunctionArgument() override;
private:
    Argument* argumentLeft;
    Argument* argumentRight;
    double(*function)(double a, double b);
};

#endif //CHRYSALIS_BINARYFUNCTION_H