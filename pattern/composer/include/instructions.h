#ifndef CHRYSALIS_INSTRUCTIONS_H
#define CHRYSALIS_INSTRUCTIONS_H

#include "arguments/PointArgument.h"
#include "arguments/VectorArgument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/BinaryFunctionArgument.h"
#include "arguments/VectorFunctionArgument.h"

#include "instructions/EdgeDartInstruction.h"
#include "instructions/MovePointInstruction.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/AdjustPointInstruction.h"
#include "instructions/RelativePointInstruction.h"
#include "instructions/UnfoldEdgeDartInstruction.h"
#include "instructions/IntersectionPointInstruction.h"

using B = Chrysalis::BinaryFunction;
using V = Chrysalis::VectorFunction;

using P = Chrysalis::PointArgument;
using Vec = Chrysalis::VectorArgument;
using D = Chrysalis::EdgeDartInstruction;
using FP = Chrysalis::FreePointInstruction;
using MP = Chrysalis::MovePointInstruction;
using Adj = Chrysalis::AdjustPointInstruction;
using UD = Chrysalis::UnfoldEdgeDartInstruction;
using RelP = Chrysalis::RelativePointInstruction;
using IP = Chrysalis::IntersectionPointInstruction;

#define common space, new args::patterns(*patterns)

#define num(val) new NumberArgument(val)
#define up num(90)
#define right num(0)
#define left num(180)
#define down num(270)

#define no_num new OptionalArgument<BaseArgument<double>>()
#define no_name new OptionalArgument<BaseArgument<std::string>>()
#define name(name) new NameArgument(PointName::name)
#define param(parameterName) new ParameterArgument(parameters->get(ParameterName::parameterName))
#define point(pointName) new args::point(name(pointName), new args::patterns(*patterns))
#define pattern(patternSpace) new PatternArgument(patternSpace)

#define use_last_point common, new OptionalArgument<PointArgument>()
#define biFunc(operator1, operator2, function) new BinaryFunctionArgument(operator1, operator2, function)
#define vecFunc(pointFrom, patternFrom, pointTo, patternTo, function) new VectorFunctionArgument(pointFrom, patternFrom, pointTo, patternTo, function)

#endif //CHRYSALIS_INSTRUCTIONS_H