#ifndef CHRYSALIS_INSTRUCTIONS_H
#define CHRYSALIS_INSTRUCTIONS_H

#include "arguments/BinaryFunctionArgument.h"
#include "arguments/VectorFunctionArgument.h"

#include "instructions/EdgeDartInstruction.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/AdjustPointInstruction.h"
#include "instructions/RelativePointInstruction.h"

using B = Chrysalis::BinaryFunction;
using V = Chrysalis::VectorFunction;

using D = Chrysalis::EdgeDartInstruction;
using P = Chrysalis::FreePointInstruction;
using Adj = Chrysalis::AdjustPointInstruction;
using RelP = Chrysalis::RelativePointInstruction;

#define common space, new SelectedPatternsArgument(selectedPatterns)

#define num(val) new NumberArgument(val)
#define up num(90)
#define right num(0)
#define left num(180)
#define down num(270)

#define no_name new NameArgument()
#define name(name) new NameArgument(PointName::name)
#define param(parameterName) new ParameterArgument(parameters->get(ParameterName::parameterName))
#define pattern(patternSpace) new PatternArgument(patternSpace)

#define use_last_point common, no_name, pattern()
#define biFunc(operator1, operator2, function) new BinaryFunctionArgument(operator1, operator2, function)
#define vecFunc(pointFrom, patternFrom, pointTo, patternTo, function) new VectorFunctionArgument(pointFrom, patternFrom, pointTo, patternTo, function)

#endif //CHRYSALIS_INSTRUCTIONS_H