#ifndef CHRYSALIS_COMPOSER_H
#define CHRYSALIS_COMPOSER_H

#include "Project.h"
#include "arguments/BinaryFunctionArgument.h"

#define param(parameterName) *new ParameterArgument(project_->getParameters()->get(ParameterName::parameterName))

#define vector_no_angle(origin, length) Proxy::Vector(point(origin), 0, length)

#define biFunc(function, operand1, operand2) new BinaryFunctionArgument::function(operand1, operand2)

namespace Chrysalis {
    const BinaryFunctionArgument& operator+(const args::number& a, const args::number& b);
    const BinaryFunctionArgument& operator-(const args::number& a, const args::number& b);
    const BinaryFunctionArgument& operator*(const args::number& a, const args::number& b);
    const BinaryFunctionArgument& operator/(const args::number& a, const args::number& b);

    const BinaryFunctionArgument& operator+(const args::number& a, double b);
    const BinaryFunctionArgument& operator-(const args::number& a, double b);
    const BinaryFunctionArgument& operator*(const args::number& a, double b);
    const BinaryFunctionArgument& operator/(const args::number& a, double b);

    const BinaryFunctionArgument& operator+(double a, const args::number& b);
    const BinaryFunctionArgument& operator-(double a, const args::number& b);
    const BinaryFunctionArgument& operator*(double a, const args::number& b);
    const BinaryFunctionArgument& operator/(double a, const args::number& b);

    const args::condition* operator<(const args::number& a, const args::number& b);
}

#endif //CHRYSALIS_COMPOSER_H