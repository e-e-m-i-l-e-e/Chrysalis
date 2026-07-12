#ifndef CHRYSALIS_COMPOSER_H
#define CHRYSALIS_COMPOSER_H

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
#include "instructions/IntersectionPointInstruction.h"
#include "instructions/PatternInstructionsContainer.h"

#include "proxies/OutlineProxy.h"
#include "proxies/LineProxy.h"
#include "proxies/RayProxy.h"
#include "proxies/NameProxy.h"
#include "proxies/VectorProxy.h"
#include "proxies/SegmentProxy.h"

#include "initializers/Instructions.h"
#include "initializers/PatternInstructions.h"

#define REPEAT_NAMES(d, data, elem) new Argument<std::string>(PointName::elem)
#define names(...) names(new args::container<Argument<std::string>>({BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(REPEAT_NAMES, ~, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))}))

#define name(arg) name(new Argument<std::string>(PointName::arg))
#define param(parameterName) *new ParameterArgument(project_->getParameters()->get(ParameterName::parameterName))
#define option(optionName) Constructs::OptionProxy(project_->getInstructions()->options()->get(Options::optionName))
#define expression(expressionName) (Constructs::lastExpression = Constructs::ExpressionProxy(Expressions::expressionName))

#define vector_no_angle(origin, length) Proxy::Vector(point(origin), 0, length)

#define biFunc(function, operand1, operand2) new BinaryFunctionArgument::function(operand1, operand2)

#define edge(from, to) Proxy::Segment(segment(from, to))

#define DART_2(from, to) seg(segment(from, to))
#define DART_3(origin, angle, length) vec(vector(origin, angle, length))

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
        struct ExpressionProxy {
            // operator const args::number*() const {
            //     return new ExpressionArgument(PatternInstructionsInitializer::patternInstructions_->expressions(), new Argument(name_));
            // }
            operator const args::number&() const {
                return *new ExpressionArgument(Composer::PatternInstructions::instructions->expressions(), new Argument(name_));
            }
            ExpressionProxy& operator=(const std::string& expression) {
                name_ = expression;
                return *this;
            }
            ExpressionInstruction* operator=(const double value) const {
                return operator=(*new Argument(value));
            }
            ExpressionInstruction* operator=(const args::number& value) const {
                return new ExpressionInstruction(Composer::Instructions::instructionsContainer->expressions(), new args::expr(name_, &value));
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
                const auto negative = new BaseInstructionsContainer<BaseInstruction>(Composer::Instructions::instructionsContainer->options(), Composer::Instructions::instructionsContainer->expressions());
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
            const auto positive = new BaseInstructionsContainer<BaseInstruction>(Composer::Instructions::instructionsContainer->options(), Composer::Instructions::instructionsContainer->expressions());
            for (const auto instruction : instructions) {
                positive->add(instruction);
            }
            return ConditionalInstructionsContainerInitializer::Negative(positive, initializer.condition_);
        }
        static ExpressionProxy lastExpression;
    }
}

#endif //CHRYSALIS_COMPOSER_H