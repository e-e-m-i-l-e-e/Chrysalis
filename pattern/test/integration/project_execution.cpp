#include <gtest/gtest.h>

#include "Project.h"
#include "FreePointInstruction.h"
#include "RelativePointInstruction.h"
#include "PatternInstructionsContainer.h"
#include "arguments/BinaryFunctionArgument.h"
#include "arguments/VectorFunctionArgument.h"

using namespace Chrysalis;

class TestProjectExecution: public ::testing::Test {
protected:
    static constexpr auto HIP_DEPTH = "Hip Depth";
    static constexpr auto BUST_SPAN = "Bust Span";
    static constexpr auto BACK_WIDTH = "Back Width";
    static constexpr auto BUST_HEIGHT = "Bust Height";
    static constexpr auto SHOULDER_LENGTH = "Shoulder Length";
    static constexpr auto HIP_CIRCUMFERENCE = "Hip Circumference";
    static constexpr auto BACK_WAIST_LENGTH = "Back Waist Length";
    static constexpr auto BUST_CIRCUMFERENCE = "Bust Circumference";
    static constexpr auto NECK_CIRCUMFERENCE = "Neck Circumference";

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

        const auto backWidth = new Parameter(BACK_WIDTH);
        backWidth->setValue(31);
        parameters_->addParameter(backWidth);

        const auto bustHeight = new Parameter(BUST_HEIGHT);
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

        const auto bustCircumference = new Parameter(BUST_CIRCUMFERENCE);
        bustCircumference->setValue(96);
        parameters_->addParameter(bustCircumference);

        const auto waistCircumference = new Parameter("Waist Circumference");
        waistCircumference->setValue(68);
        parameters_->addParameter(waistCircumference);

        const auto neckCircumference = new Parameter(NECK_CIRCUMFERENCE);
        neckCircumference->setValue(38);
        parameters_->addParameter(neckCircumference);

        const auto shoulderLength = new Parameter(SHOULDER_LENGTH);
        shoulderLength->setValue(11);
        parameters_->addParameter(shoulderLength);

        const auto hipCircumference = new Parameter(HIP_CIRCUMFERENCE);
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
#define up num(90)
#define right num(0)
#define left num(180)
#define down num(270)
#define name(name) new NameArgument(name)
#define param(parameterName) parameters_->getParameter(parameterName)
#define pattern(patternSpace) new PatternArgument(patternSpace)
#define common space_, new SelectedPatternsArgument(selectedPatterns)
#define biFunc(operator1, operator2, function) new BinaryFunctionArgument(operator1, operator2, function)
#define vecFunc(pointFrom, patternFrom, pointTo, patternTo, function) new VectorFunctionArgument(pointFrom, patternFrom, pointTo, patternTo, function)
#define use_last_point common, name(), pattern()

TEST_F(TestProjectExecution, Project1) {
    SelectedPatterns* selectedPatterns = nullptr;
    PatternInstructionsContainer* patternInstructions = nullptr;

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpace1_);
    selectedPatterns->add(patternSpace2_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);

    patternInstructions->add(new FreePointInstruction(common, name("S"), num(0.0), num(0.0)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("W"), down, param(BACK_WAIST_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("H"), down, param(HIP_DEPTH)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpace1_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);

    patternInstructions->add(new RelativePointInstruction(common, name("H"), pattern(), name("H1"), right,
                                                          biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::subtract)));
    patternInstructions->add(new RelativePointInstruction(common, name("W"), pattern(), name("W1"), right,
                                                          vecFunc(name("H"), pattern(patternSpace1_), name("H1"), pattern(patternSpace1_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name("W"), pattern(), name("W2"), right,
                                                          biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), &BinaryFunction::divide), num(1), &BinaryFunction::subtract)));
    patternInstructions->add(new RelativePointInstruction(common, name("S"), pattern(), name("S1"), right,
                                                      vecFunc(name("W"), pattern(patternSpace1_), name("W2"), pattern(patternSpace1_), &VectorFunction::length)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpace1_);
    selectedPatterns->add(patternSpace2_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);
    patternInstructions->add(new RelativePointInstruction(common, name("W"), pattern(), name("AH"), up,
                                                          biFunc(vecFunc(name("S"), pattern(patternSpace1_), name("W"), pattern(patternSpace1_), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("UB"), up,
                                                      biFunc(vecFunc(name("S"), pattern(patternSpace1_), name("AH"), pattern(patternSpace1_), &VectorFunction::length),
                                                          num(3), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name("H"), pattern(), name("T"), up,
                                                  biFunc(vecFunc(name("H"), pattern(patternSpace1_), name("W"), pattern(patternSpace1_), &VectorFunction::length),
                                                      num(2), &BinaryFunction::divide)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpace1_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);
    patternInstructions->add(new RelativePointInstruction(common, name("S"), pattern(), name("N"), right,
                                                          biFunc(param(NECK_CIRCUMFERENCE), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("N1"), down,
                                                      biFunc(param(NECK_CIRCUMFERENCE), num(16), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("N2"), left,
                                                          vecFunc(name("N"), pattern(patternSpace1_), name("S"), pattern(patternSpace1_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name("N1"), pattern(), name("N3"), left,
                                                          biFunc(vecFunc(name("N2"), pattern(patternSpace1_), name("N1"), pattern(patternSpace1_), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name("N"), pattern(), name("S2"), num(-18), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(common, name("UB"), pattern(), name("UB1"), right,
                                                          biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name("AH"), pattern(), name("AH1"), right,
                                                      biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("AH2"), num(45), num(1.5)));
    patternInstructions->add(new RelativePointInstruction(common, name("AH"), pattern(), name("AH3"), right,
                                                      vecFunc(name("W"), pattern(patternSpace1_), name("W2"), pattern(patternSpace1_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("AH4"), left, num(1)));
    patternInstructions->add(new RelativePointInstruction(common, name("N"), pattern(), name("D"), num(-18),
                                                          biFunc(vecFunc(name("N"), pattern(patternSpace1_), name("S2"), pattern(patternSpace1_), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpace2_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);

    patternInstructions->add(new RelativePointInstruction(common, name("H"), pattern(), name("H1"), left,
                                                          biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::add)));
    patternInstructions->add(new RelativePointInstruction(common, name("W"), pattern(), name("W1"), left,
                                                          vecFunc(name("H"), pattern(patternSpace1_), name("H1"), pattern(patternSpace1_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name("W"), pattern(), name("W2"), left,
                                                          biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::add)));
    patternInstructions->add(new RelativePointInstruction(common, name("S"), pattern(), name("S1"), left,
                                                          vecFunc(name("W"), pattern(patternSpace1_), name("W2"), pattern(patternSpace1_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name("S"), pattern(), name("N"), left,
                                                          biFunc(param(NECK_CIRCUMFERENCE), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("N1"), down,
                                                          biFunc(biFunc(param(NECK_CIRCUMFERENCE), num(6), &BinaryFunction::divide), num(2), &BinaryFunction::add)));
    patternInstructions->add(new RelativePointInstruction(common, name("N"), pattern(), name("S2"), num(180 + 26), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(common, name("UB"), pattern(), name("UB1"), left,
                                                          biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name("AH"), pattern(), name("AH1"), left,
                                                          biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("AH2"), num(90 + 45), num(2.5)));
    patternInstructions->add(new RelativePointInstruction(common, name("AH"), pattern(), name("AH3"), left,
                                                          vecFunc(name("W"), pattern(patternSpace1_), name("W2"), pattern(patternSpace1_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("AH4"), right, num(1)));
    patternInstructions->add(new RelativePointInstruction(common, name("S"), pattern(), name("B"), down, param(BUST_HEIGHT)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name("DA"), left,
                                                          biFunc(param(BUST_SPAN), num(2), &BinaryFunction::divide)));

    // First point is added. Both patterns share same point.
    ASSERT_NE(patternSpace1_->getLastPoint(), nullptr);
    EXPECT_EQ(patternSpace1_->getLastPoint(), patternSpace2_->getLastPoint());
    EXPECT_EQ(patternSpace1_->getLastPoint()->x(), 0);
    EXPECT_EQ(patternSpace1_->getLastPoint()->y(), 0);


}