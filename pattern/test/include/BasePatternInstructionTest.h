#ifndef CHRYSALIS_BASEPATTERNINSTRUCTIONTEST_H
#define CHRYSALIS_BASEPATTERNINSTRUCTIONTEST_H

#include <expected>
#include <gtest/gtest.h>

#include "mocks/PatternTraceObserverMock.h"

#include "Error.h"
#include "ProjectSpace.h"
#include "arguments/PatternsContainerArgument.h"

namespace Chrysalis {
    template <typename T>
    class BasePatternInstructionTest: public ::testing::TestWithParam<T> {
    protected:
        void SetUp() override;
        void TearDown() override;

        ProjectSpace* space() const;
        args::patterns* mockPatterns(size_t n);
        static args::patterns* mockPatterns();
        std::vector<PatternTraceObserverMock*>& observers();
    private:
        ProjectSpace* space_ = nullptr;
        std::vector<PatternTraceObserverMock*> mocks_;
        std::vector<std::unique_ptr<PatternSpace>> testPatternSpaces_;
    };
    using FreePointInstructionData = std::tuple<std::expected<std::string, Error>, std::expected<double, Error>, std::expected<double, Error>>;
    template class BasePatternInstructionTest<FreePointInstructionData>;
}

#endif //CHRYSALIS_BASEPATTERNINSTRUCTIONTEST_H
