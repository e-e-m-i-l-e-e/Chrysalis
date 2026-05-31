#include <gtest/gtest.h>

#include "Project.h"
#include "Argument.h"
#include "FreePointInstruction.h"

using namespace Chrysalis;

class TestProjectExecution: public ::testing::Test {
protected:
    void SetUp() override {
        space_ = new ProjectSpace();
        instructions_ = new Instructions();
        project_ = new Project("Test", space_, new Parameters(), instructions_);
    }
    void TearDown() override {
        delete project_;
    }
    Project* project_ = nullptr;
    ProjectSpace* space_ = nullptr;
    Instructions* instructions_ = nullptr;
};

TEST_F(TestProjectExecution, Pattern1) {
    instructions_->addInstruction(new FreePointInstruction(space_, new Argument<ActivePatternSpaces*>(),
                                                           new Argument<std::string>("A"),
                                                           new Argument<double>(0), new Argument<double>(0)));
}