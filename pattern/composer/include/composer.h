#ifndef CHRYSALIS_COMPOSER_H
#define CHRYSALIS_COMPOSER_H

#include "Project.h"
#include "arguments/BinaryFunctionArgument.h"

#define _min_(operand1, operand2) *new BinaryFunctionArgument::Min(&operand1, &operand2)
#define _ray_(origin, angle) Proxy::Ray(_point_(origin), angle)
#define _point_(pointName) Proxy::Name(PointName::pointName)
#define _param_(parameterName) *new ParameterArgument(project_->getParameters()->get(ParameterName::parameterName))
#define _option_(optionName) Proxy::Name(Options::optionName)
#define _outline_(outlineName) Proxy::Outline(OutlineName::outlineName)
#define _expression_(expressionName) Proxy::Name(Expressions::expressionName)

#define up 90
#define right 0
#define left 180
#define down 270

#define _angle_(from, to) *new VectorFunctionArgument::Angle(_point_(from), _point_(to))
#define _length_(from, to) *new VectorFunctionArgument::Length(_point_(from), _point_(to))

#define VECTOR_2(angle, length) Proxy::Vector(angle, length)
#define VECTOR_3(origin, angle, length) Proxy::Vector(_point_(origin), angle, length)

#define _vector_(...) BOOST_PP_OVERLOAD(VECTOR_, __VA_ARGS__)(__VA_ARGS__)

#define REPEAT_SEGMENT(d, data, elem) _segment_ elem
#define segments(...) new args::container(std::initializer_list<args::line*>{                                          \
BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(REPEAT_SEGMENT, ~, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))                \
})
#define _segment_(from, to) Proxy::Segment(new args::segment(_point_(from), _point_(to)))

#define DART_2(from, to) seg(_segment_(from, to))
#define DART_3(origin, angle, length) vec(_vector_(origin, angle, length))

#define dart(...) BOOST_PP_OVERLOAD(DART_, __VA_ARGS__)(__VA_ARGS__)
#define edge(from, to) Proxy::Segment(_segment_(from, to))

namespace Chrysalis {
    const Argument<double>& operator""_(long double number);

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