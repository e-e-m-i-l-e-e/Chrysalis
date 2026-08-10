#include <gtest/gtest.h>

#include "Project.h"
#include "projects/Project1Composer.h"

#include "arguments/ParameterArgument.h"
#include "arguments/VectorFunctionArgument.h"

#include "instructions/FreePointInstruction.h"

using namespace Chrysalis;

class TestProject1: public ::testing::Test {
protected:
    void SetUp() override {
        project_ = Project1Composer::createProject();
        composer_ = new Project1Composer(project_);
        composer_->fill();

        project_->getInstructions()->execute();
        
        back_ = composer_->getBack();
        front_ = composer_->getFront();
    }
    void TearDown() override {
        delete project_;
        delete composer_;
    }
    Project* project_ = nullptr;
    Project1Composer* composer_ = nullptr;
    
    PatternSpace* back_ = nullptr;
    PatternSpace* front_ = nullptr;
};

TEST_F(TestProject1, Project1) {
    // ASSERT_EQ(composer_->expectedBack.size(), back_->getPoints().size());
    // for (const auto& [name, point]: composer_->expectedBack) {
    //     ASSERT_TRUE(back_->hasPoint(name));
    //     EXPECT_NEAR(back_->getPoint(name)->x(), point.first, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
    //     EXPECT_NEAR(back_->getPoint(name)->y(), point.second, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
    // }
    // ASSERT_EQ(composer_->expectedFront.size(), front_->getPoints().size());
    // for (const auto& [name, point]: composer_->expectedFront) {
    //     ASSERT_TRUE(front_->hasPoint(name));
    //     EXPECT_NEAR(front_->getPoint(name)->x(), point.first, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
    //     EXPECT_NEAR(front_->getPoint(name)->y(), point.second, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
    // }
}