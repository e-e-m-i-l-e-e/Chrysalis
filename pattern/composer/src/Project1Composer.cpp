#include "projects/Project1Composer.h"

#include "composer.h"

#include "arguments/ParameterArgument.h"
#include "arguments/VectorFunctionArgument.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"
#include "initializers/ConditionalInstructionsContainerInitializer.h"

#include "proxies/RayProxy.h"
#include "proxies/NameProxy.h"
#include "proxies/LineProxy.h"
#include "proxies/PointProxy.h"
#include "proxies/VectorProxy.h"
#include "proxies/SegmentProxy.h"
#include "proxies/OutlineProxy.h"
#include "proxies/ConditionProxy.h"

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
    options->add(Option::createDefault(Options::HAS_ADDITIONAL_FRONT_DARTS, true));
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

#define Block Composer::Instructions(project_) << std::initializer_list<std::vector<BaseInstruction*>>
#define If(condition) Composer::ConditionalInstructionsContainerInitializer(condition) << std::initializer_list<std::vector<BaseInstruction*>>
#define Else << std::initializer_list<std::vector<BaseInstruction*>>

#define REPEAT_NAMES(d, data, elem) new Argument<std::string>(PointName::elem)
#define names(...) names(new args::container<Argument<std::string>>({BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(REPEAT_NAMES, ~, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))}))

#define name(arg) name(new Argument<std::string>(PointName::arg))

void Project1Composer::fillInstructions() {
    Block {
        Use(back, front) {
            _point_(S)(0, 0),
            _vector_(down, _param_(BACK_WAIST_LENGTH))              -> name(W),
            _vector_(down, _param_(HIP_DEPTH))                      -> name(H)
        },
        Use(back) {
            _vector_(H, right, _param_(HIP_CIRCUMFERENCE) / 4 - 1)  -> name(H1),
            _vector_(W, right, _length_(H, H1))                     -> name(W1),
            _vector_(W, right, _param_(BUST_CIRCUMFERENCE) / 4 - 1) -> name(W2),
            _vector_(S, right, _length_(W, W2))                     -> name(S1)
        },
        Use(back, front) {
            _vector_(W, up, _length_(S, W) / 2)                     -> name(AH),
            _vector_(up, _length_(S, AH) / 3)                       -> name(UB),
            _vector_(H, up, _length_(H, W) / 2)                     -> name(T)
        },
        Use(back) {
            _vector_(S, right, _param_(NECK_CIRCUMFERENCE) / 6)     -> name(N),
            _vector_(down, _param_(NECK_CIRCUMFERENCE) / 16)        -> name(N1),
            _vector_(left, _length_(N, S))                          -> name(N2),
            _vector_(N1, left, _length_(N2, N1) / 2)                -> name(N3),
            _vector_(N, -18, _param_(SHOULDER_LENGTH))              -> name(S2),
            _vector_(UB, right, _param_(BACK_WIDTH) / 2)            -> name(UB1),
            _vector_(AH, right, _param_(BACK_WIDTH) / 2)            -> name(AH1),
            _vector_(45, 1.5)                                     -> name(AH2),
            _vector_(AH, right, _length_(W, W2))                    -> name(AH3),
            _vector_(left, 1)                                     -> name(AH4),
            _vector_(N, -18, _length_(N, S2) / 2)                   -> name(D),
            edge(N, S2) -> dart(D, 90, 7)(2)
        },
        _expression_(INTAKE) = _param_(BUST_CIRCUMFERENCE) + _param_(HIP_CIRCUMFERENCE),
        _expression_(MAX_INTAKE) = 2 + 4 + (2 << _option_(HAS_CENTER_BACK_DART) >> 0),
        If(_expression_(MAX_INTAKE) < _expression_(INTAKE)) {
            _expression_(COEFFICIENT) = _min_(1._, (_expression_(INTAKE) / (_expression_(MAX_INTAKE) + 2. / 3 * 2)))
        } Else {
            _expression_(COEFFICIENT) = _expression_(INTAKE) / _expression_(MAX_INTAKE)
        },
        Use(back) {
            _vector_(W, right, 2 * _expression_(COEFFICIENT))   -> name(W3),
            _vector_(W2, left, 4 * _expression_(COEFFICIENT))   -> name(W4)
        },
        If(_option_(HAS_CENTER_BACK_DART)) {
            Use(back) {
                _vector_(W3, right, (_length_(W3, W4) / 3))         -> name(DW1),
                _vector_(W4, left, (_length_(W3, W4) / 3))          -> name(DW2),
                _vector_(90, _length_(AH, W) - 2) << _point_(DW2)(2. / 3 * 2 * _expression_(COEFFICIENT)) >> _vector_(-90, 9)
            }
        } Else {
            Use(back) {
                _vector_(W3, right, _length_(W3, W4) / 2)           -> name(DW1)
            }
        },
        Use(back) {
            _vector_(90, _length_(AH, W)) << _point_(DW1)(2 * _expression_(COEFFICIENT)) >> _vector_(-90, 11)
        },
        Use(front) {
            _vector_(H, left, _param_(HIP_CIRCUMFERENCE) / 4 + 1)   -> name(H1),
            _vector_(W, left, _length_(H, H1))                      -> name(W1),
            _vector_(W, left, _param_(BUST_CIRCUMFERENCE) / 4 + 1)  -> name(W2),
            _vector_(S, left, _length_(W, W2))                      -> name(S1),
            _vector_(S, left, _param_(NECK_CIRCUMFERENCE) / 6)      -> name(N),
            _vector_(down, _param_(NECK_CIRCUMFERENCE) / 6 + 2)     -> name(N1),
            _vector_(N, 180 + 26, _param_(SHOULDER_LENGTH))         -> name(S2),
            _vector_(UB, left, _param_(BACK_WIDTH) / 2)             -> name(UB1),
            _vector_(AH, left, _param_(BACK_WIDTH) / 2)             -> name(AH1),
            _vector_(90 + 45, 2.5)                                -> name(AH2),
            _vector_(AH, left, _length_(W, W2))                     -> name(AH3),
            _vector_(right, 1)                                    -> name(AH4),
            _vector_(S, down, _param_(BUST_HEIGHT))                 -> name(B),
            _vector_(left, _param_(BUST_SPAN) / 2)                  -> name(DA),
            _vector_(DA, 0, _param_(APEX_TO_CENTER_FRONT)) -> name(N2) | _segment_(H, S),
            _vector_(left, _length_(S, N))                          -> name(N1),
            _vector_(N, down, _length_(N1, N) / 3)                  -> name(N3),
            _vector_(N2, left, _length_(N1, N2) / 3)                -> name(N4),
            _vector_(DA, 0, _param_(APEX_TO_SHOULDER)) >> _point_(S2) << _vector_(N, 0, _param_(SHOULDER_LENGTH)),
            _vector_(N, _angle_(N, S2), _length_(N, S2) / 2)          -> name(D1),
            edge(N, S2) -> dart(D1, DA)((_param_(BUST_CIRCUMFERENCE) / 20 + 1) * 2),
            (_segment_(UB, UB1) | segments((D1, DA), (D1_1, DA))) -> names(UB1_1, UB1_2),
            (_segment_(AH, AH1) | segments((D1, DA), (D1_1, DA))) -> names(AH1_1, AH1_2),
            (_ray_(AH2, 0) | segments((D1, DA), (D1_1, DA))) -> names(AH1_3, AH1_4),
            _segment_(UB1_1, UB1_2) >> _point_(UB1),
            _segment_(AH1_1, AH1_2) >> _point_(AH1),
            _segment_(AH1_1, AH1_2) >> _point_(AH3),
            _segment_(AH1_1, AH1_2) >> _point_(AH4),
            _segment_(AH1_3, AH1_4) >> _point_(AH2),
            _segment_(N, N3) & _segment_(N2, N4)
        },
        _expression_(INTAKE) = ((_param_(BUST_CIRCUMFERENCE) + _param_(HIP_CIRCUMFERENCE)) / 2 - _param_(WAIST_CIRCUMFERENCE)) / 4,
        _expression_(MAX_INTAKE) = 3 + 4,
        If (_expression_(MAX_INTAKE) < _expression_(INTAKE)) {
            _expression_(COEFFICIENT) = _min_(1._, (_expression_(INTAKE) / (_expression_(MAX_INTAKE) + 2. / 3. * 3.)))
        } Else {
            _expression_(COEFFICIENT) = _expression_(INTAKE) / _expression_(MAX_INTAKE)
        },
        Use(front) {
            _vector_(W2, right, 4 * _expression_(COEFFICIENT))                     -> name(W3),
            _vector_(DA, down, _length_(B, W))                     -> name(DW1),
            _vector_(90, _length_(DA, DW1)) << _point_(DW1)(3 * _expression_(COEFFICIENT)) >> _vector_(-90, 9)
        },
        If(_option_(HAS_ADDITIONAL_FRONT_DARTS)) {
            Use(front) {
                _vector_(W3, right, _length_(W3, DW1) / 2)                                    -> name(DW2),
                _vector_(90, _length_(DA, DW1) - 2) << _point_(DW2)(2. / 3. * 3. * _expression_(COEFFICIENT)) >> _vector_(-90, 7)
            }
        },
        Use(back) {
            _outline_(MAIN) >> _point_(S2) >> _point_(AH3)
                               >> _point_(W4) >> _point_(H1) >> _point_(H) >> _point_(W3) >> _point_(UB)
                               >> _point_(N2) >> _point_(N) >> _point_(D1) >> _point_(DA) >> _point_(D2)
        },
        Use(front) {
            _outline_(MAIN) >> _point_(S2) >> _point_(AH3) >> _point_(W3) >> _point_(H1) >> _point_(H)
                               >> _point_(N2) >> _point_(N) >> _point_(D1) >> _point_(DA) >> _point_(D1_1)
        }
    };
}
