#include <gtest/gtest.h>

#include "Project.h"

#include "arguments/ParameterArgument.h"
#include "arguments/BinaryFunctionArgument.h"
#include "arguments/VectorFunctionArgument.h"

#include "instructions/FreePointInstruction.h"
#include "instructions/BuildOutlineInstruction.h"
#include "instructions/RelativePointInstruction.h"
#include "instructions/PatternInstructionsContainer.h"

using namespace Chrysalis;

#define common space_, new SelectedPatternsArgument(selectedPatterns)

#define num(val) new NumberArgument(val)
#define up num(90)
#define right num(0)
#define left num(180)
#define down num(270)

#define name(name) new NameArgument(name)
#define param(parameterName) new ParameterArgument(parameters_->get(parameterName))
#define pattern(patternSpace) new PatternArgument(patternSpace)

#define use_last_point common, name(), pattern()
#define biFunc(operator1, operator2, function) new BinaryFunctionArgument(operator1, operator2, function)
#define vecFunc(pointFrom, patternFrom, pointTo, patternTo, function) new VectorFunctionArgument(pointFrom, patternFrom, pointTo, patternTo, function)

class TestProjectExecution: public ::testing::Test {
protected:
    static constexpr auto S = "S";
    static constexpr auto S1 = "S1";
    static constexpr auto S2 = "S2";
    
    static constexpr auto N = "N";
    static constexpr auto N1 = "N1";
    static constexpr auto N2 = "N2";
    static constexpr auto N3 = "N3";
    
    static constexpr auto AH = "AH";
    static constexpr auto AH1 = "AH1";
    static constexpr auto AH2 = "AH2";
    static constexpr auto AH3 = "AH3";
    static constexpr auto AH4 = "AH4";
    
    static constexpr auto UB = "UB";
    static constexpr auto UB1 = "UB1";
    
    static constexpr auto W = "W";
    static constexpr auto W1 = "W1";
    static constexpr auto W2 = "W2";
    
    static constexpr auto T = "T";
    
    static constexpr auto H = "H";
    static constexpr auto H1 = "H1";
    
    static constexpr auto B = "B";
    static constexpr auto D = "D";
    static constexpr auto DA = "DA";
    
    static constexpr auto HIP_DEPTH = "Hip Depth";
    static constexpr auto BUST_SPAN = "Bust Span";
    static constexpr auto BACK_WIDTH = "Back Width";
    static constexpr auto BUST_HEIGHT = "Bust Height";
    static constexpr auto SHOULDER_LENGTH = "Shoulder Length";
    static constexpr auto APEX_TO_SHOULDER = "Apex to shoulder";
    static constexpr auto HIP_CIRCUMFERENCE = "Hip Circumference";
    static constexpr auto BACK_WAIST_LENGTH = "Back Waist Length";
    static constexpr auto BUST_CIRCUMFERENCE = "Bust Circumference";
    static constexpr auto NECK_CIRCUMFERENCE = "Neck Circumference";
    static constexpr auto WAIST_CIRCUMFERENCE = "Waist Circumference";
    static constexpr auto APEX_TO_CENTER_FRONT = "Apex to center-front";

    void SetUp() override {
        patterns_ = new PatternsContainer();

        outlineBack_ = new OutlineContainer();
        patternSpaceBack_ = new PatternSpace(outlineBack_);
        patternBack_ = new Pattern("Back", patternSpaceBack_);
        patterns_->add(patternBack_);

        outlineFront_ = new OutlineContainer();
        patternSpaceFront_ = new PatternSpace(outlineFront_);
        patternFront_ = new Pattern("Front", patternSpaceFront_);
        patterns_->add(patternFront_);

        parameters_ = new ParametersContainer();
        const auto backWaistLength = new Parameter(BACK_WAIST_LENGTH);
        backWaistLength->setValue(42);
        parameters_->add(backWaistLength);

        const auto backWidth = new Parameter(BACK_WIDTH);
        backWidth->setValue(31);
        parameters_->add(backWidth);

        const auto bustHeight = new Parameter(BUST_HEIGHT);
        bustHeight->setValue(28);
        parameters_->add(bustHeight);

        const auto bustSpan = new Parameter(BUST_SPAN);
        bustSpan->setValue(17);
        parameters_->add(bustSpan);

        const auto apexToCenterFront = new Parameter(APEX_TO_CENTER_FRONT);
        apexToCenterFront->setValue(21);
        parameters_->add(apexToCenterFront);

        const auto apexToShoulder = new Parameter(APEX_TO_SHOULDER);
        apexToShoulder->setValue(27);
        parameters_->add(apexToShoulder);

        const auto hipDepth = new Parameter(HIP_DEPTH);
        hipDepth->setValue(21.5);
        parameters_->add(hipDepth);

        const auto bustCircumference = new Parameter(BUST_CIRCUMFERENCE);
        bustCircumference->setValue(96);
        parameters_->add(bustCircumference);

        const auto waistCircumference = new Parameter(WAIST_CIRCUMFERENCE);
        waistCircumference->setValue(68);
        parameters_->add(waistCircumference);

        const auto neckCircumference = new Parameter(NECK_CIRCUMFERENCE);
        neckCircumference->setValue(38);
        parameters_->add(neckCircumference);

        const auto shoulderLength = new Parameter(SHOULDER_LENGTH);
        shoulderLength->setValue(11);
        parameters_->add(shoulderLength);

        const auto hipCircumference = new Parameter(HIP_CIRCUMFERENCE);
        hipCircumference->setValue(98);
        parameters_->add(hipCircumference);

        space_ = new ProjectSpace();
        instructions_ = new InstructionsContainer();
        project_ = new Project("Bodice", space_, parameters_, patterns_, instructions_);
    }
    void TearDown() override {
        delete project_;
    }
    Project* project_ = nullptr;
    ProjectSpace* space_ = nullptr;
    PatternsContainer* patterns_ = nullptr;
    ParametersContainer* parameters_ = nullptr;
    InstructionsContainer* instructions_ = nullptr;

    Pattern* patternBack_ = nullptr;
    PatternSpace* patternSpaceBack_ = nullptr;
    OutlineContainer* outlineBack_ = nullptr;

    Pattern* patternFront_ = nullptr;
    PatternSpace* patternSpaceFront_ = nullptr;
    OutlineContainer* outlineFront_ = nullptr;
};

TEST_F(TestProjectExecution, Project1) {
    SelectedPatterns* selectedPatterns = nullptr;
    PatternInstructionsContainer* patternInstructions = nullptr;

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpaceBack_);
    selectedPatterns->add(patternSpaceFront_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);

    patternInstructions->add(new FreePointInstruction(common, name(S), num(0.0), num(0.0)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(W), down, param(BACK_WAIST_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(H), down, param(HIP_DEPTH)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpaceBack_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);

    patternInstructions->add(new RelativePointInstruction(common, name(H), pattern(), name(H1), right,
                                                          biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::subtract)));
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(W1), right,
                                                          vecFunc(name(H), pattern(patternSpaceBack_), name(H1), pattern(patternSpaceBack_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(W2), right,
                                                          biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::subtract)));
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(S1), right,
                                                      vecFunc(name(W), pattern(patternSpaceBack_), name(W2), pattern(patternSpaceBack_), &VectorFunction::length)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpaceBack_);
    selectedPatterns->add(patternSpaceFront_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(AH), up,
                                                          biFunc(vecFunc(name(S), pattern(patternSpaceBack_), name(W), pattern(patternSpaceBack_), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(UB), up,
                                                      biFunc(vecFunc(name(S), pattern(patternSpaceBack_), name(AH), pattern(patternSpaceBack_), &VectorFunction::length),
                                                          num(3), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name(H), pattern(), name(T), up,
                                                  biFunc(vecFunc(name(H), pattern(patternSpaceBack_), name(W), pattern(patternSpaceBack_), &VectorFunction::length),
                                                      num(2), &BinaryFunction::divide)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpaceBack_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(N), right,
                                                          biFunc(param(NECK_CIRCUMFERENCE), num(6), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(N1), down,
                                                      biFunc(param(NECK_CIRCUMFERENCE), num(16), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(N2), left,
                                                          vecFunc(name(N), pattern(patternSpaceBack_), name(S), pattern(patternSpaceBack_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name(N1), pattern(), name(N3), left,
                                                          biFunc(vecFunc(name(N2), pattern(patternSpaceBack_), name(N1), pattern(patternSpaceBack_), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name(N), pattern(), name(S2), num(-18), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(common, name(UB), pattern(), name(UB1), right,
                                                          biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name(AH), pattern(), name(AH1), right,
                                                      biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(AH2), num(45), num(1.5)));
    patternInstructions->add(new RelativePointInstruction(common, name(AH), pattern(), name(AH3), right,
                                                      vecFunc(name(W), pattern(patternSpaceBack_), name(W2), pattern(patternSpaceBack_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(AH4), left, num(1)));
    patternInstructions->add(new RelativePointInstruction(common, name(N), pattern(), name(D), num(-18),
                                                          biFunc(vecFunc(name(N), pattern(patternSpaceBack_), name(S2), pattern(patternSpaceBack_), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpaceFront_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);

    patternInstructions->add(new RelativePointInstruction(common, name(H), pattern(), name(H1), left,
                                                          biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::add)));
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(W1), left,
                                                          vecFunc(name(H), pattern(patternSpaceFront_), name(H1), pattern(patternSpaceFront_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(W2), left,
                                                          biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::add)));
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(S1), left,
                                                          vecFunc(name(W), pattern(patternSpaceFront_), name(W2), pattern(patternSpaceFront_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(N), left,
                                                          biFunc(param(NECK_CIRCUMFERENCE), num(6), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(N1), down,
                                                          biFunc(biFunc(param(NECK_CIRCUMFERENCE), num(6), &BinaryFunction::divide),
                                                              num(2), &BinaryFunction::add)));
    patternInstructions->add(new RelativePointInstruction(common, name(N), pattern(), name(S2), num(180 + 26), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(common, name(UB), pattern(), name(UB1), left,
                                                          biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name(AH), pattern(), name(AH1), left,
                                                          biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(AH2), num(90 + 45), num(2.5)));
    patternInstructions->add(new RelativePointInstruction(common, name(AH), pattern(), name(AH3), left,
                                                          vecFunc(name(W), pattern(patternSpaceFront_), name(W2), pattern(patternSpaceFront_), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(AH4), right, num(1)));
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(B), down, param(BUST_HEIGHT)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(DA), left,
                                                          biFunc(param(BUST_SPAN), num(2), &BinaryFunction::divide)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpaceBack_);
    selectedPatterns->add(patternSpaceFront_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, name(), name(AH3)));
    patternInstructions->add(new BuildOutlineInstruction(common, name(), name(H1)));
    patternInstructions->add(new BuildOutlineInstruction(common, name(), name(H)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpaceBack_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);
    patternInstructions->add(new BuildOutlineInstruction(common, name(), name(UB)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(patternSpaceBack_);
    selectedPatterns->add(patternSpaceFront_);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions_->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, name(), name(N2)));
    patternInstructions->add(new BuildOutlineInstruction(common, name(), name(N)));

    static const std::unordered_map<std::string, std::pair<double, double>> expectedBack = {
        {S, {0.0, 0.0}},
        {W, {0.0, -42.0}},
        {H, {0.0, -63.5}},
        {H1, {23.5, -63.5}},
        {W1, {23.5, -42.0}},
        {W2, {23.0, -42.0}},
        {S1, {23.0, 0.0}},
        {AH, {0.0, -21.0}},
        {UB, {0.0, -14.0}},
        {T, {0.0, -52.75}},
        {N, {6.3333, 0.0}},
        {N1, {6.3333, -2.375}},
        {N2, {0.0, -2.375}},
        {N3, {3.1666, -2.375}},
        {S2, {16.795, -3.3992}},
        {AH1, {15.5, -21.0}},
        {UB1, {15.5, -14.0}},
        {AH2, {16.5606, -19.9393}},
        {AH3, {23.0, -21.0}},
        {AH4, {22.0, -21.0}},
        {D, {11.5641, -1.6995}},
    };
    static const std::unordered_map<std::string, std::pair<double, double>> expectedFront = {
        {S, {0.0, 0.0}},
        {W, {0.0, -42.0}},
        {H, {0.0, -63.5}},
        {AH, {0.0, -21.0}},
        {UB, {0.0, -14.0}},
        {T, {0.0, -52.75}},
        {H1, {-25.5, -63.5}},
        {W1, {-25.5, -42.0}},
        {W2, {-25.0, -42.0}},
        {S1, {-25.0, 0.0}},
        {N, {-6.333333333333333, 0.0}},
        {N1, {-6.333333333333333, -8.3333}},
        {S2, {-16.22, -4.822}},
        {UB1, {-15.5, -14.0}},
        {AH1, {-15.5, -21.0}},
        {AH2, {-17.2678, -19.23223304703363}},
        {AH3, {-25.0, -21.0}},
        {AH4, {-24.0, -21.0}},
        {B, {0.0, -28.0}},
        {DA, {-8.5, -28.0}},
    };
    ASSERT_EQ(expectedBack.size(), patternSpaceBack_->getPoints().size());
    for (const auto& [name, point]: expectedBack) {
        ASSERT_TRUE(patternSpaceBack_->hasPoint(name));
        EXPECT_NEAR(patternSpaceBack_->getPoint(name)->x(), point.first, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
        EXPECT_NEAR(patternSpaceBack_->getPoint(name)->y(), point.second, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
    }
    ASSERT_EQ(expectedFront.size(), patternSpaceFront_->getPoints().size());
    for (const auto& [name, point]: expectedFront) {
        ASSERT_TRUE(patternSpaceFront_->hasPoint(name));
        EXPECT_NEAR(patternSpaceFront_->getPoint(name)->x(), point.first, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
        EXPECT_NEAR(patternSpaceFront_->getPoint(name)->y(), point.second, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
    }
}