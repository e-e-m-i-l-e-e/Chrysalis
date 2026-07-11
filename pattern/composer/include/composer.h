#ifndef CHRYSALIS_INSTRUCTIONS_H
#define CHRYSALIS_INSTRUCTIONS_H

#include "composer.h"
#include "Project.h"
#include "arguments/ExpressionArgument.h"
#include "arguments/PatternPointArgument.h"
#include "arguments/VectorArgument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/Argument.h"
#include "arguments/BinaryFunctionArgument.h"
#include "arguments/VectorFunctionArgument.h"
#include "arguments/ConditionalArgument.h"
#include "instructions/ConditionalInstructionsContainer.h"

#include "instructions/EdgeDartInstruction.h"
#include "instructions/ExpressionInstruction.h"
#include "instructions/MovePointInstruction.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/RelativePointInstruction.h"
#include "instructions/UnfoldEdgeDartInstruction.h"
#include "instructions/IntersectionPointInstruction.h"
#include "instructions/PatternInstructionsContainer.h"

#define common Constructs::InstructionsInitializer::space, new args::patterns(*Constructs::PatternInstructionsInitializer::patterns_)

#define num(val) new Argument<double>(val)
#define up 90
#define right 0
#define left 180
#define down 270

#define addPoint(pointName) Constructs::FreePointInstructionProxy(new Argument<std::string>(PointName::pointName))
#define no_num new OptionalArgument<BaseArgument<double>>()
#define no_name new OptionalArgument<Argument<std::string>>()
#define name(name) pointName(new Argument<std::string>(PointName::name))
#define param(parameterName) *new ParameterArgument(project_->getParameters()->get(ParameterName::parameterName))
#define option(optionName) Constructs::OptionProxy(project_->getInstructions()->options()->get(Options::optionName))
#define expression(expressionName) (Constructs::lastExpression = Constructs::ExpressionProxy(Expressions::expressionName))
#define point(pointName) new PatternPointArgument(new Argument<std::string>(PointName::pointName), new args::patterns(*Constructs::PatternInstructionsInitializer::patterns_))
#define segment(from, to) new args::segment(point(from), point(to))
#define vector_no_angle(origin, length) new VectorArgument(point(origin), length)
#define ray(origin, angle) new args::ray(point(origin), angle)

#define VECTOR_2(angle, length) Constructs::VectorArgumentProxy(angle, length)
#define VECTOR_3(origin, angle, length) Constructs::VectorArgumentProxy(point(origin), angle, length)

#define vector(...) BOOST_PP_OVERLOAD(VECTOR_, __VA_ARGS__)(__VA_ARGS__)

#define angle(from, to) *new VectorFunctionArgument::Angle(point(from), point(to))
#define length(from, to) *new VectorFunctionArgument::Length(point(from), point(to))
#define vecFunc(function, from, to) new VectorFunctionArgument::function(from, to)
#define biFunc(function, operand1, operand2) new BinaryFunctionArgument::function(operand1, operand2)

#define edge(from, to) Constructs::Edge(segment(from, to))

#define DART_2(from, to) setLeg(segment(from, to))
#define DART_3(origin, angle, length) setVector(vector(origin, angle, length))

#define dart(...) BOOST_PP_OVERLOAD(DART_, __VA_ARGS__)(__VA_ARGS__)

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

    namespace Constructs {
        struct InstructionsInitializer {
            explicit InstructionsInitializer(const Project* project): prevInstructions(instructionsContainer) {
                space = project->getSpace();
                instructionsContainer = project->getInstructions();
            }
            ~InstructionsInitializer() {
                instructionsContainer = prevInstructions;
            }
            void operator<<(const std::initializer_list<BaseInstruction*>& instructions) const {
                for (const auto& instruction : instructions) {
                    instructionsContainer->add(instruction);
                }
            }
            static inline ProjectSpace* space = nullptr;
            static inline InstructionsContainer* instructionsContainer = nullptr;
        private:
            InstructionsContainer* prevInstructions;
        };
        struct PatternInstructionsInitializer {
            explicit PatternInstructionsInitializer(args::patterns* patterns) {
                patterns_ = patterns;
                patternInstructions_ = new PatternInstructionsContainer(
                    InstructionsInitializer::instructionsContainer->options(),
                    InstructionsInitializer::instructionsContainer->expressions(),
                    patterns_
                );
            }
            BaseInstruction* operator<<(const std::initializer_list<BasePatternInstruction*>& instructions) const {
                for (const auto& instruction : instructions) {
                    patternInstructions_->add(instruction);
                }
                return patternInstructions_;
            }
            static inline args::patterns* patterns_ = nullptr;
            static inline PatternInstructionsContainer* patternInstructions_ = nullptr;
        };
        struct FreePointInstructionProxy {
            FreePointInstruction* operator()(const double x, const double y) const {
                return new FreePointInstruction(common, name_, num(x), num(y));
            }
            const args::name* name_;
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
            explicit VectorArgumentProxy(const args::point* origin, const args::number& angle,
                                         const args::number& length)
                : vector_(new VectorArgument(origin, &angle, &length)) {}
            explicit VectorArgumentProxy(const args::point* origin, const double angle, const args::number& length)
                : vector_(new VectorArgument(origin, new Argument(angle), &length)) {}
            explicit VectorArgumentProxy(const args::point* origin, const args::number* angle, const double length)
                : vector_(new VectorArgument(origin, angle, new Argument(length))) {}
            explicit VectorArgumentProxy(const args::point* origin, const double angle, const double length)
                : vector_(new VectorArgument(origin, new Argument(angle), new Argument(length))) {}

            explicit VectorArgumentProxy(const args::number& angle, const args::number& length)
                : vector_(new VectorArgument(&angle, &length)) {}
            explicit VectorArgumentProxy(const double angle, const double length)
                : vector_(new VectorArgument(new Argument(angle), new Argument(length))) {}
            explicit VectorArgumentProxy(const double angle, const args::number& length)
                : vector_(new VectorArgument(new Argument(angle), &length)) {}

            operator const args::vector*() const {
                return vector_;
            }
            RelativePointInstructionProxy operator->() const {
                return RelativePointInstructionProxy(vector_);
            }
            args::vector* vector_;
        };
        struct UnfoldEdgeDartInstructionProxy {
            UnfoldEdgeDartInstruction* operator()(const args::number& intake) const {
                return new UnfoldEdgeDartInstruction(common, segment1_, segment2_, &intake);
            }
            const args::segment* segment1_;
            const args::segment* segment2_;
        };
        struct EdgeDartInstructionProxy {
            explicit EdgeDartInstructionProxy(const args::segment* segment): segment_(segment) {}
            EdgeDartInstructionProxy& setVector(const VectorArgumentProxy vector) {
                vector_ = vector.vector_;
                return *this;
            }
            UnfoldEdgeDartInstructionProxy setLeg(const args::segment* segment) const {
                return UnfoldEdgeDartInstructionProxy(segment_, segment);
            }
            EdgeDartInstruction* operator()(const double intake) const {
                return new EdgeDartInstruction(common, segment_, vector_, new Argument(intake), new args::optional<args::number>());
            }
            EdgeDartInstructionProxy* operator->() {
                return this;
            }
            args::vector* vector_ = nullptr;
            const args::segment* segment_;
        };
        struct Edge {
            EdgeDartInstructionProxy operator->() const {
                return EdgeDartInstructionProxy(segment_);
            }
            const args::segment* segment_;
        };
        struct ExpressionProxy {
            // operator const args::number*() const {
            //     return new ExpressionArgument(PatternInstructionsInitializer::patternInstructions_->expressions(), new Argument(name_));
            // }
            operator const args::number&() const {
                return *new ExpressionArgument(PatternInstructionsInitializer::patternInstructions_->expressions(), new Argument(name_));
            }
            ExpressionProxy& operator=(const std::string& expression) {
                name_ = expression;
                return *this;
            }
            ExpressionInstruction* operator=(const double value) const {
                return operator=(*new Argument(value));
            }
            ExpressionInstruction* operator=(const args::number& value) const {
                return new ExpressionInstruction(InstructionsInitializer::instructionsContainer->expressions(), new args::expr(name_, &value));
            }
            std::string name_;
        };
        struct OptionProxy {
            struct Positive;
            struct Negative;
            operator const Option*() const {
                return option_;
            }
            const Option* option_;
        };
        struct ConditionalInstructionsContainerInitializer {
            struct Negative;
            const args::condition* condition_;
        };
        struct OptionProxy::Positive {
            const OptionProxy option_;
            const args::number* positive_;
        };
        struct ConditionalInstructionsContainerInitializer::Negative {
            ConditionalInstructionsContainer* operator<<(const std::initializer_list<BaseInstruction*>& instructions) const {
                const auto negative = new BaseInstructionsContainer<BaseInstruction>(InstructionsInitializer::instructionsContainer->options(), InstructionsInitializer::instructionsContainer->expressions());
                for (const auto instruction : instructions) {
                    negative->add(instruction);
                }
                return new ConditionalInstructionsContainer(condition_, positive_, negative);
            }
            const BaseInstructionsContainer<BaseInstruction>* positive_;
            const args::condition* condition_;
        };
        inline OptionProxy::Positive operator<<(const double number, const OptionProxy& option) {
            return OptionProxy::Positive(option, new Argument(number));
        }
        inline args::conditional& operator>>(const OptionProxy::Positive& option, const double number) {
            return *new args::conditional(option.option_, option.positive_, new Argument(number));
        }
        inline ConditionalInstructionsContainerInitializer::Negative operator<<(const ConditionalInstructionsContainerInitializer& initializer, std::initializer_list<BaseInstruction*> instructions) {
            const auto positive = new BaseInstructionsContainer<BaseInstruction>(InstructionsInitializer::instructionsContainer->options(), InstructionsInitializer::instructionsContainer->expressions());
            for (const auto instruction : instructions) {
                positive->add(instruction);
            }
            return ConditionalInstructionsContainerInitializer::Negative(positive, initializer.condition_);
        }
        static ExpressionProxy lastExpression;
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