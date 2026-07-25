#ifndef CHRYSALIS_NAMEPROXY_H
#define CHRYSALIS_NAMEPROXY_H

#include "Option.h"
#include "PointProxy.h"
#include "ConditionProxy.h"
#include "arguments/ConditionalArgument.h"
#include "arguments/ExpressionArgument.h"
#include "arguments/VectorArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis::Proxy {
    class Name {
    public:
        class Vector;
        class Number;
        explicit Name(const std::string& name);

        operator const Option*() const;
        operator const args::name*() const;
        operator const args::number&() const;
        operator const PatternPointArgument*() const;

        Number operator=(double value) const;
        Number operator=(const args::number& number) const;
        const args::condition* operator<(const Name& other) const;
        Proxy::Number::Point operator()(const args::number& number) const;
        std::vector<BasePatternInstruction*> operator()(double x, double y) const;
    private:
        const args::name* name_;
    };
    Condition::Number operator<<(double value, const Name& name);
    class Name::Vector {
    public:
        class Line;
        explicit Vector(const args::name* name, const args::vector* vector);
        operator std::vector<BasePatternInstruction*>() const;
        Line operator|(const args::line* line) const;
    private:
        const args::name* name_;
        const args::vector* vector_;
    };
    class Name::Vector::Line {
    public:
        explicit Line(const args::name* name, const args::vector* vector, const args::line* line);
        operator std::vector<BasePatternInstruction*>() const;
    private:
        const args::name* name_;
        const args::line* line_;
        const args::vector* vector_;
    };
    class Name::Number {
    public:
        explicit Number(const args::name* name, const args::number* number);
        operator std::vector<BaseInstruction*>() const;
    private:
        const args::name* name_;
        const args::number* number_;
    };
}

#endif //CHRYSALIS_NAMEPROXY_H
