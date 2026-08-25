#include "BasePatternInstructionTest.h"

using namespace Chrysalis;

template<typename T>
void BasePatternInstructionTest<T>::SetUp() {
    space_ = new ProjectSpace();
}

template<typename T>
void BasePatternInstructionTest<T>::TearDown() {
    delete space_;
    for (const auto& mock: mocks_) delete mock;
}

template<typename T>
ProjectSpace* BasePatternInstructionTest<T>::space() const {
    return space_;
}

template<typename T>
args::patterns* BasePatternInstructionTest<T>::mockPatterns(const size_t n) {
    const auto patterns = new PatternsContainerArgument();
    for (size_t i = 0; i < n; ++i) {
        const auto patternSpace = PatternSpace::create();
        testPatternSpaces_.push_back(std::unique_ptr<PatternSpace>(patternSpace));
        const auto observer = new PatternTraceObserverMock();
        patternSpace->trace::addObserver(observer);
        patterns->add(patternSpace);
        mocks_.push_back(observer);
    }
    return patterns;
}

template<typename T>
args::patterns* BasePatternInstructionTest<T>::mockPatterns() {
    return new PatternsContainerArgument();
}

template<typename T>
std::vector<PatternTraceObserverMock*>& BasePatternInstructionTest<T>::observers() {
    return mocks_;
}