#include <gtest/gtest.h>

#include "Project.h"
#include "FreePointInstruction.h"
#include "PatternInstructionsContainer.h"

using namespace Chrysalis;

class TestProjectExecution: public ::testing::Test {
protected:
    void SetUp() override {
        space_ = new ProjectSpace();
        patterns_ = new PatternsContainer();
        instructions_ = new InstructionsContainer();
        project_ = new Project("Test", space_, new Parameters(), patterns_, instructions_);

        patternSpace1_ = new PatternSpace();
        pattern1_ = new Pattern("Pattern 1", patternSpace1_);
        patterns_->add(pattern1_);

        patternSpace2_ = new PatternSpace();
        pattern2_ = new Pattern("Pattern 2", patternSpace2_);
        patterns_->add(pattern2_);
    }
    void TearDown() override {
        delete project_;
    }
    Project* project_ = nullptr;
    ProjectSpace* space_ = nullptr;
    PatternsContainer* patterns_ = nullptr;
    InstructionsContainer* instructions_ = nullptr;

    Pattern* pattern1_ = nullptr;
    PatternSpace* patternSpace1_ = nullptr;

    Pattern* pattern2_ = nullptr;
    PatternSpace* patternSpace2_ = nullptr;
};

#define num(val) new NumberArgument(val)
#define name(name) new NameArgument(name)

TEST_F(TestProjectExecution, Project1) {
    const auto patterns = new SelectedPatterns();
    const auto patternInstructions = new PatternInstructionsContainer(patterns);

    patternInstructions->add(new FreePointInstruction(space_, new SelectedPatternsArgument(patterns),
                                                           name("A"), num(0.0), num(0.0)));
    instructions_->add(patternInstructions);
    instructions_->execute();

    // First point is added. Both patterns share same point.
    EXPECT_EQ(patternSpace1_->getLastPoint(), patternSpace2_->getLastPoint());
    EXPECT_EQ(patternSpace1_->getLastPoint()->x(), 0);
    EXPECT_EQ(patternSpace1_->getLastPoint()->y(), 0);
}