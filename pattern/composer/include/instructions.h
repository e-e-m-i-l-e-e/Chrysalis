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

using Vec = Chrysalis::VectorArgument;
using D = Chrysalis::EdgeDartInstruction;
using FP = Chrysalis::FreePointInstruction;
using MP = Chrysalis::MovePointInstruction;
using UD = Chrysalis::UnfoldEdgeDartInstruction;
using RelP = Chrysalis::RelativePointInstruction;
using IP = Chrysalis::IntersectionPointInstruction;

#define common space, new args::patterns(*patterns)

#define num(val) new Argument<double>(val)
#define up num(90)
#define right num(0)
#define left num(180)
#define down num(270)

#define no_num new OptionalArgument<BaseArgument<double>>()
#define no_name new OptionalArgument<Argument<std::string>>()
#define name(name) new Argument<std::string>(PointName::name)
#define param(parameterName) (new ParameterArgument(parameters->get(ParameterName::parameterName)))
#define option(optionName) project_->getInstructions()->options()->get(Options::optionName)
#define expression(expressionName) new ExpressionArgument(project_->getInstructions()->expressions(), new Argument<std::string>(Expressions::expressionName))
#define point(pointName) new PatternPointArgument(name(pointName), new args::patterns(*patterns))
#define segment(from, to) new args::segment(point(from), point(to))
#define vector_no_angle(origin, length) new args::vector(point(origin), length)
#define ray(origin, angle) new args::ray(point(origin), angle)
#define vector_(origin, angle, length) new args::vector(point(origin), angle, length)
#define vector_0(angle, length) new args::vector(angle, length)

#define vecFunc(function, from, to) new VectorFunctionArgument::function(from, to)
#define biFunc(function, operand1, operand2) new BinaryFunctionArgument::function(operand1, operand2)

#endif //CHRYSALIS_INSTRUCTIONS_H