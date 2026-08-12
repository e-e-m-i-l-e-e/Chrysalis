#include <array>
#include <random>
#include <functional>
#include <gtest/gtest.h>
#include <boost/preprocessor/seq/size.hpp>

#include "arguments/BinaryFunctionArgument.h"

#include "mocks/NumberMock.h"
#include "ArgumentEvaluationData.h"

using namespace Chrysalis;

TEST(BinaryFunctionArgument_Test, Error) {
    using ::testing::Return;

    auto num1 = std::make_unique<NumberMock>();
    auto num2 = std::make_unique<NumberMock>();
    auto num3 = std::make_unique<NumberMock>();

    static const auto ERROR_MESSAGE = "ERROR";

    EXPECT_CALL(*num1, get).WillRepeatedly(Return(1));
    EXPECT_CALL(*num2, get).WillRepeatedly(Return(std::unexpected(Error{ERROR_MESSAGE})));

    // Represents expression: num1 + num2 * num3
    const BinaryFunctionArgument::Add biFunction(std::move(num1),
                                                 std::make_unique<BinaryFunctionArgument::Multiply>(
                                                     std::move(num2),
                                                     std::move(num3)
                                                 )
    );
    ASSERT_FALSE(biFunction.get().has_value());
    ASSERT_EQ(biFunction.get().error().message(), ERROR_MESSAGE);
}

TEST(BinaryFunctionArgument_Test, Evaluation) {
    using ::testing::Return;

    static constexpr size_t NUMBER_OF_OPERANDS = 7;

    std::array<double, NUMBER_OF_OPERANDS> nums = {1.8, 7, 4.3, 2, 9, 6.6, 0};
    std::vector<std::unique_ptr<NumberMock>> mocks(NUMBER_OF_OPERANDS);
    for (size_t i = 0; i < NUMBER_OF_OPERANDS; ++i) {
        mocks[i] = std::make_unique<NumberMock>();
        EXPECT_CALL(*mocks[i], get).WillRepeatedly(Return(nums[i]));
    }
    // Represents expression: (max(num1, num2) + num3) / num4 - (min(num5, num6) * num7)
    //                        (max( 1.8,    7) +  4.3) /    2 - (min(   9,  6.6) *    0)
    const BinaryFunctionArgument::Subtract biFunction(
        std::move(std::make_unique<BinaryFunctionArgument::Divide>(
            std::move(std::make_unique<BinaryFunctionArgument::Add>(
                std::move(std::make_unique<BinaryFunctionArgument::Max>(std::move(mocks[0]), std::move(mocks[1]))),
                std::move(mocks[2]))), std::move(mocks[3]))), std::move(
            std::make_unique<BinaryFunctionArgument::Multiply>(
                std::move(std::make_unique<BinaryFunctionArgument::Min>(std::move(mocks[4]), std::move(mocks[5]))),
                std::move(mocks[6]))));
    ASSERT_TRUE(biFunction.get().has_value());
    ASSERT_EQ(biFunction.get().value(), 5.65);
}

#define BINARY_FUNCTION_FACTORY_METHODS ((OP)(+)) ((OP)(-)) ((OP)(*)) ((OP)(/)) ((STD)(min)) ((STD)(max))

#define BINARY_FUNCTION_FACTORY_IMPL(index, evaluator, name)                                                           \
    [](const ArgumentEvaluationData& rhs, const ArgumentEvaluationData& lhs) {                                         \
        return ArgumentEvaluationData(                                                                                 \
            new BinaryFunctionArgument::BOOST_PP_SEQ_ELEM(index, BINARY_FUNCTIONS)                                     \
                (args::number(rhs.expression()), args::number(lhs.expression())),                                      \
            name, evaluator                                                                                            \
        );                                                                                                             \
    },

#define BINARY_FUNCTION_FACTORY_OP(index, sign)                                                                        \
    BINARY_FUNCTION_FACTORY_IMPL(                                                                                      \
        index,                                                                                                         \
        rhs.expected() sign lhs.expected(),                                                                            \
        std::string("(") + rhs.expressionText() + " " + BOOST_PP_STRINGIZE(sign) + " " + lhs.expressionText() + ")"    \
    )

#define BINARY_FUNCTION_FACTORY_STD(index, function)                                                                   \
    BINARY_FUNCTION_FACTORY_IMPL(                                                                                      \
        index,                                                                                                         \
        std::function(rhs.expected(), lhs.expected()),                                                                 \
        std::string("std::") + BOOST_PP_STRINGIZE(function) +                                                          \
                               "(" + rhs.expressionText() + ", " + lhs.expressionText() + ")"                          \
    )

#define APPLY_ENTRY(type, payload, index) BOOST_PP_CAT(BINARY_FUNCTION_FACTORY_, type)(index, payload)

#define BINARY_FUNCTION_FACTORY_ENTRY(r, data, i, elem)                                                                \
    APPLY_ENTRY(BOOST_PP_SEQ_ELEM(0, elem), BOOST_PP_SEQ_ELEM(1, elem), i)

class BinaryFunctionArgument_Evaluation: public ::testing::TestWithParam<ArgumentEvaluationData> {};

TEST_P(BinaryFunctionArgument_Evaluation, Evaluation) {
    const auto& [expression, expressionText, expected] = GetParam();
    ASSERT_EQ(expression->get().value(), expected) << expressionText;
}

INSTANTIATE_TEST_SUITE_P(
    DataDriven,
    BinaryFunctionArgument_Evaluation,
    testing::ValuesIn([] {
        using ::testing::Return;
        static std::vector<args::number> pool_;
        std::mt19937 generator{std::random_device{}()};

        static constexpr size_t NUMBER_OF_TESTS = 10;
        static constexpr size_t MAX_NUMBER_OF_OPERANDS = 50;

        static constexpr std::size_t NUM_OF_FUNCTIONS = BOOST_PP_SEQ_SIZE(BINARY_FUNCTIONS);
        using BinaryFunctionFactory = std::function<ArgumentEvaluationData(const ArgumentEvaluationData& rhs, const ArgumentEvaluationData& lhs)>;
        const std::array<BinaryFunctionFactory, NUM_OF_FUNCTIONS> factories = {
            BOOST_PP_SEQ_FOR_EACH_I(BINARY_FUNCTION_FACTORY_ENTRY, ~, BINARY_FUNCTION_FACTORY_METHODS)
        };

        std::vector<ArgumentEvaluationData> testData;
        testData.reserve(NUMBER_OF_TESTS);

        for (size_t i = 0; i < NUMBER_OF_TESTS; ++i) {
            std::vector<double> operands(std::uniform_int_distribution<size_t>{2, MAX_NUMBER_OF_OPERANDS}(generator));
            for (double& operand: operands) {
                operand = std::uniform_real_distribution{}(generator);
            }
            auto compose = [&](auto&& self, const int start, const int end) -> ArgumentEvaluationData {
                if (start == end) {
                    const auto num = new NumberMock();
                    EXPECT_CALL(*num, get).WillRepeatedly(Return(operands[start]));
                    return ArgumentEvaluationData(num, std::to_string(operands[start]), operands[start]);
                }
                int index = std::uniform_int_distribution{0, static_cast<int>(NUM_OF_FUNCTIONS - 1)}(generator);
                std::uniform_int_distribution distribution{start + 1, end};
                auto separator = distribution(generator);
                return factories[index](self(self, start, separator - 1), self(self, separator, end));
            };
            ArgumentEvaluationData data = compose(compose, 0, static_cast<int>(operands.size()) - 1);
            testData.push_back(data);
            pool_.emplace_back(data.expression());
        }
        return testData;
    }())
);

#undef BINARY_FUNCTION_FACTORY_OP
#undef BINARY_FUNCTION_FACTORY_STD
#undef BINARY_FUNCTION_FACTORY_IMPL
#undef BINARY_FUNCTION_FACTORY_ENTRY
#undef BINARY_FUNCTION_FACTORY_METHODS