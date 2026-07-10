#ifndef CHRYSALIS_INSTRUCTIONS_H
#define CHRYSALIS_INSTRUCTIONS_H

#include "arguments/ExpressionArgument.h"
#include "arguments/PatternPointArgument.h"
#include "arguments/VectorArgument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/Argument.h"
#include "arguments/BinaryFunctionArgument.h"
#include "arguments/VectorFunctionArgument.h"
#include "arguments/ConditionalArgument.h"

#include "instructions/EdgeDartInstruction.h"
#include "instructions/MovePointInstruction.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/RelativePointInstruction.h"
#include "instructions/UnfoldEdgeDartInstruction.h"
#include "instructions/IntersectionPointInstruction.h"
#include "instructions/PatternInstructionsContainer.h"

#define common Constructs::space, new args::patterns(*Constructs::patterns)

#define num(val) new Argument<double>(val)
#define up num(90)
#define right num(0)
#define left num(180)
#define down num(270)

#define no_num new OptionalArgument<BaseArgument<double>>()
#define no_name new OptionalArgument<Argument<std::string>>()
#define name(name) pointName(new Argument<std::string>(PointName::name))
#define param(parameterName) *new ParameterArgument(project_->getParameters()->get(ParameterName::parameterName))
#define option(optionName) project_->getInstructions()->options()->get(Options::optionName)
#define expression(expressionName) new ExpressionArgument(project_->getInstructions()->expressions(), new Argument<std::string>(Expressions::expressionName))
#define point(pointName) new PatternPointArgument(new Argument<std::string>(PointName::pointName), new args::patterns(*Constructs::patterns))
#define segment(from, to) new args::segment(point(from), point(to))
#define vector_no_angle(origin, length) new VectorArgument(point(origin), length)
#define ray(origin, angle) new args::ray(point(origin), angle)

#define VECTOR_2(angle, length) Constructs::VectorArgumentProxy(new VectorArgument(angle, length))
#define VECTOR_3(origin, angle, length) Constructs::VectorArgumentProxy(new VectorArgument(point(origin), angle, length))

#define vector(...) BOOST_PP_OVERLOAD(VECTOR_, __VA_ARGS__)(__VA_ARGS__)

#define vecFunc(function, from, to) new VectorFunctionArgument::function(from, to)
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

    namespace Constructs {
        static ProjectSpace* space;
        static args::patterns* patterns;
        static PatternInstructionsContainer* patternInstructions;

        struct PatternInstructionsInitializer {
            explicit PatternInstructionsInitializer(const std::initializer_list<BasePatternInstruction*>& instructions) {
                for (const auto& instruction : instructions) {
                    patternInstructions->add(instruction);
                }
            }
        };
        struct RelativePointInstructionProxy {
            RelativePointInstructionProxy* operator->() {
                return this;
            }
            RelativePointInstruction* pointName(const args::name* name) const {
                return new RelativePointInstruction(common, name, vector_);
            }
            const args::vector* vector_;
        };
        struct VectorArgumentProxy {
            operator const args::vector*() const {
                return vector_;
            }
            RelativePointInstructionProxy operator->() const {
                return RelativePointInstructionProxy(vector_);
            }
            const args::vector* vector_;
        };
    }
}

using Vec = Chrysalis::VectorArgument;
using D = Chrysalis::EdgeDartInstruction;
using FP = Chrysalis::FreePointInstruction;
using MP = Chrysalis::MovePointInstruction;
using UD = Chrysalis::UnfoldEdgeDartInstruction;
using RelP = Chrysalis::RelativePointInstruction;
using IP = Chrysalis::IntersectionPointInstruction;

#endif //CHRYSALIS_INSTRUCTIONS_H