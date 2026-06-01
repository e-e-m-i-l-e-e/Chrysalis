#include <gtest/gtest.h>

#include "Project.h"
#include "FreePointInstruction.h"
#include "PatternInstructionsContainer.h"
#include "RelativePointInstruction.h"

using namespace Chrysalis;

class TestProjectExecution: public ::testing::Test {
protected:
    static constexpr auto HIP_DEPTH = "Hip Depth";
    static constexpr auto BACK_WAIST_LENGTH = "Back Waist Length";
    void SetUp() override {
        patterns_ = new PatternsContainer();

        patternSpace1_ = new PatternSpace();
        pattern1_ = new Pattern("Back", patternSpace1_);
        patterns_->add(pattern1_);

        patternSpace2_ = new PatternSpace();
        pattern2_ = new Pattern("Front", patternSpace2_);
        patterns_->add(pattern2_);

        parameters_ = new Parameters();
        const auto backWaistLength = new Parameter(BACK_WAIST_LENGTH);
        backWaistLength->setValue(42);
        parameters_->addParameter(backWaistLength);

        const auto backWidth = new Parameter("Back Width");
        backWidth->setValue(31);
        parameters_->addParameter(backWidth);

        const auto bustHeight = new Parameter("Bust Height");
        bustHeight->setValue(28);
        parameters_->addParameter(bustHeight);

        const auto bustSpan = new Parameter("Bust Span");
        bustSpan->setValue(17);
        parameters_->addParameter(bustSpan);

        const auto apexToCenterFront = new Parameter("Apex to center-front");
        apexToCenterFront->setValue(21);
        parameters_->addParameter(apexToCenterFront);

        const auto apexToShoulder = new Parameter("Apex to shoulder");
        apexToShoulder->setValue(27);
        parameters_->addParameter(apexToShoulder);

        const auto hipDepth = new Parameter(HIP_DEPTH);
        hipDepth->setValue(21.5);
        parameters_->addParameter(hipDepth);

        const auto bustCircumference = new Parameter("Bust Circumference");
        bustCircumference->setValue(96);
        parameters_->addParameter(bustCircumference);

        const auto waistCircumference = new Parameter("Waist Circumference");
        waistCircumference->setValue(68);
        parameters_->addParameter(waistCircumference);

        const auto neckCircumference = new Parameter("Neck Circumference");
        neckCircumference->setValue(38);
        parameters_->addParameter(neckCircumference);

        const auto shoulderLength = new Parameter("Shoulder Length");
        shoulderLength->setValue(11);
        parameters_->addParameter(shoulderLength);

        const auto hipCircumference = new Parameter("Hip Circumference");
        hipCircumference->setValue(98);
        parameters_->addParameter(hipCircumference);

        space_ = new ProjectSpace();
        instructions_ = new InstructionsContainer();
        project_ = new Project("Bodice", space_, parameters_, patterns_, instructions_);
    }
    void TearDown() override {
        delete project_;
    }
    Project* project_ = nullptr;
    ProjectSpace* space_ = nullptr;
    Parameters* parameters_ = nullptr;
    PatternsContainer* patterns_ = nullptr;
    InstructionsContainer* instructions_ = nullptr;

    Pattern* pattern1_ = nullptr;
    PatternSpace* patternSpace1_ = nullptr;

    Pattern* pattern2_ = nullptr;
    PatternSpace* patternSpace2_ = nullptr;
};

#define num(val) new NumberArgument(val)
#define down num(270)
#define name(name) new NameArgument(name)
#define param(parameterName) parameters_->getParameter(parameterName)
#define pattern(patternSpace) new PatternArgument(patternSpace)
#define common space_, new SelectedPatternsArgument(selectedPatterns)
#define use_last_point common, name(), pattern()

TEST_F(TestProjectExecution, Project1) {
    SelectedPatterns* selectedPatterns = nullptr;
    PatternInstructionsContainer* patternInstructions = nullptr;

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpace1_);
    selectedPatterns->add(patternSpace2_);

    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    patternInstructions->add(new FreePointInstruction(common, name("S"), num(0.0), num(0.0)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("W"), down, param(BACK_WAIST_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("H"), down, param(HIP_DEPTH)));
    instructions_->add(patternInstructions);

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpace1_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    // patternInstructions->add()

    instructions_->execute();

    // First point is added. Both patterns share same point.
    ASSERT_NE(patternSpace1_->getLastPoint(), nullptr);
    EXPECT_EQ(patternSpace1_->getLastPoint(), patternSpace2_->getLastPoint());
    EXPECT_EQ(patternSpace1_->getLastPoint()->x(), 0);
    EXPECT_EQ(patternSpace1_->getLastPoint()->y(), 0);


}

TEST_F(TestProjectExecution, Project2) {
    const auto selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpace1_);

    const auto patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    patternInstructions->add(new FreePointInstruction(common, name("A"), num(0.0), num(0.0)));
    instructions_->add(patternInstructions);

    instructions_->execute();

    // First point is added to pattern1.
    ASSERT_NE(patternSpace1_->getLastPoint(), nullptr);
    EXPECT_EQ(patternSpace2_->getLastPoint(), nullptr);
    EXPECT_EQ(patternSpace1_->getLastPoint()->x(), 0);
    EXPECT_EQ(patternSpace1_->getLastPoint()->y(), 0);
}