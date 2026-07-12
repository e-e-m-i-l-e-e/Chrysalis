#include "../include/projects/Project1Composer.h"

#include "composer.h"
#include "instructions/BuildOutlineInstruction.h"

#include "AssociativeContainer.h"
#include "CompositiveContainer.h"

#include "Option.h"
#include "Outline.h"
#include "Pattern.h"

#include "instructions/BaseInstruction.h"
#include "instructions/BasePatternInstruction.h"
#include "arguments/ComparisonArgument.h"
#include "arguments/ParameterArgument.h"
#include "instructions/ConditionalInstructionsContainer.h"
#include "instructions/CurveInstruction.h"
#include "instructions/DartInstruction.h"
#include "instructions/ExpressionInstruction.h"
#include "instructions/PatternInstructionsContainer.h"

using namespace Chrysalis;

Project1Composer::Project1Composer(Project* project): BaseProjectComposer(project) {}

Project* Project1Composer::createProject() {
    return Project::create("Project1Composer");
}

PatternSpace* Project1Composer::getBack() const {
    return back_->getSpace();
}

PatternSpace* Project1Composer::getFront() const {
    return front_->getSpace();
}

void Project1Composer::fillOptions() {
    const auto options = project_->getOptions();
    options->add(Option::createDefault(Options::HAS_CENTER_BACK_DART, true));
}

void Project1Composer::fillPatterns() {
    const auto patterns = project_->getPatterns();
    back_ = Pattern::create("Back");
    back_->getSpace()->getOutline()->add(new Outline("main"));
    patterns->add(back_);
    front_ = Pattern::create("Front");
    front_->getSpace()->getOutline()->add(new Outline("main"));
    patterns->add(front_);
}

void Project1Composer::fillParameters() {
    const auto parameters = project_->getParameters();
    parameters->add(Parameter::createDefault(ParameterName::BACK_WAIST_LENGTH, 42));
    parameters->add(Parameter::createDefault(ParameterName::BACK_WIDTH, 31));
    parameters->add(Parameter::createDefault(ParameterName::BUST_HEIGHT, 28));
    parameters->add(Parameter::createDefault(ParameterName::BUST_SPAN, 17));
    parameters->add(Parameter::createDefault(ParameterName::APEX_TO_CENTER_FRONT, 21));
    parameters->add(Parameter::createDefault(ParameterName::APEX_TO_SHOULDER, 27));
    parameters->add(Parameter::createDefault(ParameterName::HIP_DEPTH, 21.5));
    parameters->add(Parameter::createDefault(ParameterName::BUST_CIRCUMFERENCE, 96));
    parameters->add(Parameter::createDefault(ParameterName::WAIST_CIRCUMFERENCE, 68));
    parameters->add(Parameter::createDefault(ParameterName::NECK_CIRCUMFERENCE, 38));
    parameters->add(Parameter::createDefault(ParameterName::SHOULDER_LENGTH, 11));
    parameters->add(Parameter::createDefault(ParameterName::HIP_CIRCUMFERENCE, 98));
}

#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>

#define GET_PATTERN_NAME(r, data, i, elem) BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(elem, _)->getSpace()

#define Use(...)                                                                                                       \
Composer::PatternInstructions(new args::patterns({                                                                     \
    BOOST_PP_SEQ_FOR_EACH_I(                                                                                           \
        GET_PATTERN_NAME, _,                                                                                           \
        BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)                                                                          \
    )                                                                                                                  \
})) << std::initializer_list<std::vector<BasePatternInstruction*>>                                                                  \

#define Block Composer::Instructions(project_) << std::initializer_list<BaseInstruction*>
#define If(condition) Constructs::ConditionalInstructionsContainerInitializer(condition) << std::initializer_list<BaseInstruction*>
#define Else << std::initializer_list<BaseInstruction*>
void Project1Composer::fillInstructions() {
    Block {
        Use(back, front) {
            point(S)(0, 0),
            vector(down, param(BACK_WAIST_LENGTH))              -> name(W),
            vector(down, param(HIP_DEPTH))                      -> name(H)
        },
        Use(back) {
            vector(H, right, param(HIP_CIRCUMFERENCE) / 4 - 1)  -> name(H1),
            vector(W, right, length(H, H1))                     -> name(W1),
            vector(W, right, param(BUST_CIRCUMFERENCE) / 4 - 1) -> name(W2),
            vector(S, right, length(W, W2))                     -> name(S1)
        },
        Use(back, front) {
            vector(W, up, length(S, W) / 2)                     -> name(AH),
            vector(up, length(S, AH) / 3)                       -> name(UB),
            vector(H, up, length(H, W) / 2)                     -> name(T)
        },
        Use(back) {
            vector(S, right, param(NECK_CIRCUMFERENCE) / 6)     -> name(N),
            vector(down, param(NECK_CIRCUMFERENCE) / 16)        -> name(N1),
            vector(left, length(N, S))                          -> name(N2),
            vector(N1, left, length(N2, N1) / 2)                -> name(N3),
            vector(N, -18, param(SHOULDER_LENGTH))              -> name(S2),
            vector(UB, right, param(BACK_WIDTH) / 2)            -> name(UB1),
            vector(AH, right, param(BACK_WIDTH) / 2)            -> name(AH1),
            vector(45, 1.5)                                     -> name(AH2),
            vector(AH, right, length(W, W2))                    -> name(AH3),
            vector(left, 1)                                     -> name(AH4),
            vector(N, -18, length(N, S2) / 2)                   -> name(D),
            edge(N, S2) -> dart(D, 90, 7)(2)
        },
        expression(INTAKE) = param(BUST_CIRCUMFERENCE) + param(HIP_CIRCUMFERENCE),
        expression(MAX_INTAKE) = 2 + 4 + (2 << option(HAS_CENTER_BACK_DART) >> 0),
        If(expression(MAX_INTAKE) < expression(INTAKE)) {
            expression(COEFFICIENT) = *biFunc(Min, new Argument(1.), &(expression(INTAKE) / (expression(MAX_INTAKE) + 2. / 3 * 2)))
        } Else {
            expression(COEFFICIENT) = expression(INTAKE) / expression(MAX_INTAKE)
        },
        Use(back) {
            vector(W, right, 2 * expression(COEFFICIENT))   -> name(W3),
            vector(W2, left, 4 * expression(COEFFICIENT))   -> name(W4)
        },
        If(option(HAS_CENTER_BACK_DART)) {
            Use(back) {
                vector(W3, right, (length(W3, W4) / 3))         -> name(DW1),
                vector(W4, left, (length(W3, W4) / 3))          -> name(DW2),
                vector(90, length(AH, W) - 2) << point(DW2)(2. / 3 * 2 * expression(COEFFICIENT)) >> vector(-90, 9)
            }
        } Else {
            Use(back) {
                vector(W3, right, length(W3, W4) / 2)           -> name(DW1)
            }
        },
        Use(back) {
            vector(90, length(AH, W)) << point(DW1)(2 * expression(COEFFICIENT)) >> vector(-90, 11)
        },
        Use(front) {
            vector(H, left, param(HIP_CIRCUMFERENCE) / 4 + 1)   -> name(H1),
            vector(W, left, length(H, H1))                      -> name(W1),
            vector(W, left, param(BUST_CIRCUMFERENCE) / 4 + 1)  -> name(W2),
            vector(S, left, length(W, W2))                      -> name(S1),
            vector(S, left, param(NECK_CIRCUMFERENCE) / 6)      -> name(N),
            vector(down, param(NECK_CIRCUMFERENCE) / 6 + 2)     -> name(N1),
            vector(N, 180 + 26, param(SHOULDER_LENGTH))         -> name(S2),
            vector(UB, left, param(BACK_WIDTH) / 2)             -> name(UB1),
            vector(AH, left, param(BACK_WIDTH) / 2)             -> name(AH1),
            vector(90 + 45, 2.5)                                -> name(AH2),
            vector(AH, left, length(W, W2))                     -> name(AH3),
            vector(right, 1)                                    -> name(AH4),
            vector(S, down, param(BUST_HEIGHT))                 -> name(B),
            vector(left, param(BUST_SPAN) / 2)                  -> name(DA),
            vector(DA, 0, param(APEX_TO_CENTER_FRONT)) -> name(N2) | segment(H, S),
            vector(left, length(S, N))                          -> name(N1),
            vector(N, down, length(N1, N) / 3)                  -> name(N3),
            vector(N2, left, length(N1, N2) / 3)                -> name(N4),
            vector_no_angle(DA, param(APEX_TO_SHOULDER)) >> point(S2) << vector_no_angle(N, param(SHOULDER_LENGTH)),
            vector(N, angle(N, S2), length(N, S2) / 2)          -> name(D1),
            edge(N, S2) -> dart(D1, DA)((param(BUST_CIRCUMFERENCE) / 20 + 1) * 2),
            (segment(UB, UB1) | segments((D1, DA), (D1_1, DA))) -> names(UB1_1, UB1_2),
            (segment(AH, AH1) | segments((D1, DA), (D1_1, DA))) -> names(AH1_1, AH1_2),
            (ray(AH2, 0) | segments((D1, DA), (D1_1, DA))) -> names(AH1_3, AH1_4),
            segment(UB1_1, UB1_2) >> point(UB1),
            segment(AH1_1, AH1_2) >> point(AH1),
            segment(AH1_1, AH1_2) >> point(AH3),
            segment(AH1_1, AH1_2) >> point(AH4),
            segment(AH1_3, AH1_4) >> point(AH2),
            segment(N, N3) & segment(N2, N4)
        },
        expression(INTAKE) = ((param(BUST_CIRCUMFERENCE) + param(HIP_CIRCUMFERENCE)) / 2 - param(WAIST_CIRCUMFERENCE)) / 4,
        expression(MAX_INTAKE) = 3 + 4,
        Use(back, front) {
            outline(MAIN) >> point(AH3) >> point(H1) >> point(H)
        },
        Use(back) {
            outline(MAIN) >> point(UB)
        },
        Use(back, front) {
            outline(MAIN) >> point(N2) >> point(N)
        }
    };
}
