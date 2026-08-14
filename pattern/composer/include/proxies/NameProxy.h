#ifndef CHRYSALIS_NAMEPROXY_H
#define CHRYSALIS_NAMEPROXY_H

#include "Option.h"
#include "PointProxy.h"
#include "ConditionProxy.h"
#include "arguments/ConditionalArgument.h"
#include "arguments/ExpressionArgument.h"
#include "arguments/OptionArgument.h"
#include "arguments/VectorArgument.h"
#include "instructions/BasePatternInstruction.h"
#include "instructions/ExpressionInstruction.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/RelativePointInstruction.h"

/** @defgroup Proxy
 * @{
 */
namespace Chrysalis::Proxy {
    class Name {
    public:
        class Vector;
        class Number;
        explicit Name(const std::string& name);

        operator args::name();
        operator args::number();
        operator const OptionArgument*();
        operator const PatternPointArgument*();

        Number operator=(double value);
        Number operator=(args::number&& number);
        const args::condition* operator<(Name&& other);
        Proxy::Number::Point operator()(args::number&& number);
        FreePointInstruction* operator()(double x, double y);
    private:
        args::name name_;
    };
    Condition::Number operator<<(double value, Name&& name);
    class Name::Vector {
    public:
        class Line;
        explicit Vector(args::name&& name, const args::vector* vector);
        operator RelativePointInstruction*();
        Line operator|(const args::line* line);
    private:
        args::name name_;
        const args::vector* vector_;
    };
    class Name::Vector::Line {
    public:
        explicit Line(args::name&& name, const args::vector* vector, const args::line* line);
        operator RelativePointInstruction*();
    private:
        args::name name_;
        const args::line* line_;
        const args::vector* vector_;
    };
    class Name::Number {
    public:
        explicit Number(args::name&& name, args::number&& number);
        operator ExpressionInstruction*();
    private:
        args::name name_;
        args::number number_;
    };
}

#endif //CHRYSALIS_NAMEPROXY_H
