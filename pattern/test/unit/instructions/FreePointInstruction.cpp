#include <gtest/gtest.h>

#include "mocks/NameMock.h"
#include "mocks/NumberMock.h"
#include "BasePatternInstructionTest.h"

#include "instructions/FreePointInstruction.h"

using namespace Chrysalis;

class FreePointInstruction_Test: public BasePatternInstructionTest<FreePointInstructionData> {
protected:
    static auto mockArguments() {
        return std::make_tuple(
            std::make_unique<NameMock>(POINT_NAME),
            std::make_unique<NumberMock>(),
            std::make_unique<NumberMock>()
        );
    }
public:
    static constexpr auto POINT_NAME = "POINT_NAME";
};

class FreePointInstruction_TestValid: public FreePointInstruction_Test {};
TEST_P(FreePointInstruction_TestValid, Execution) {
    using ::testing::Return;
    using ::testing::SaveArg;

    const Point* point = nullptr;
    auto [nameValue, xValue, yValue] = GetParam();
    auto [name, x, y] = mockArguments();
    const auto patterns = mockPatterns(3);

    EXPECT_CALL(*name, get).WillRepeatedly(Return(nameValue));
    EXPECT_CALL(*x, get).WillRepeatedly(Return(xValue));
    EXPECT_CALL(*y, get).WillRepeatedly(Return(yValue));

    for (const auto& observer: observers()) {
        EXPECT_CALL(*observer, pointAdded).WillOnce(SaveArg<0>(&point));
    }

    FreePointInstruction instruction(space(), patterns, std::move(name), std::move(x), std::move(y));
    instruction.execute();

    for (const auto& pattern: *patterns) {
        ASSERT_TRUE(pattern->hasPoint(POINT_NAME));
        ASSERT_EQ(pattern->getLastPoint(), point);
        ASSERT_EQ(pattern->getPoint(POINT_NAME), point);
        ASSERT_EQ(pattern->getPoints().size(), 1);
        ASSERT_EQ(pattern->getPoint(POINT_NAME)->x(), xValue);
        ASSERT_EQ(pattern->getPoint(POINT_NAME)->y(), yValue);
    }
}
INSTANTIATE_TEST_SUITE_P(
    Correct,
    FreePointInstruction_TestValid,
    testing::Values(
        std::make_tuple(FreePointInstruction_Test::POINT_NAME, 5.5, -10.3)
    )
);

class FreePointInstruction_TestInvalid: public FreePointInstruction_Test {};
TEST_P(FreePointInstruction_TestInvalid, Error) {
    using ::testing::Return;
    auto [nameValue, xValue, yValue] = GetParam();
    auto [nameMock, xMock, yMock] = mockArguments();
    const auto patterns = mockPatterns(3);

    EXPECT_CALL(*nameMock, get).WillRepeatedly(Return(nameValue));
    EXPECT_CALL(*xMock, get).WillRepeatedly(Return(xValue));
    EXPECT_CALL(*yMock, get).WillRepeatedly(Return(yValue));

    for (const auto& observer: observers()) {
        EXPECT_CALL(*observer, pointAdded).Times(0);
    }

    FreePointInstruction instruction(space(), patterns, std::move(nameMock), std::move(xMock), std::move(yMock));
    instruction.execute();

    for (const auto& pattern: *patterns) {
        ASSERT_FALSE(pattern->hasPoint(POINT_NAME));
    }
}
INSTANTIATE_TEST_SUITE_P(
    Error,
    FreePointInstruction_TestInvalid,
    testing::Values(
        std::make_tuple(std::unexpected(Error{"Invalid point name"}), 0, 0),
        std::make_tuple(FreePointInstruction_Test::POINT_NAME, std::unexpected(Error{"Cannot get \"x\" position"}), 0),
        std::make_tuple(FreePointInstruction_Test::POINT_NAME, 0, std::unexpected(Error{"Cannot get \"y\" position"}))
    )
);