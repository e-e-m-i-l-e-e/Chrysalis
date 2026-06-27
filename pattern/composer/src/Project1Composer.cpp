#include "Project1Composer.h"

#include "instructions.h"
#include "instructions/BuildOutlineInstruction.h"

#include "arguments/ParameterArgument.h"

using namespace Chrysalis;

Project1Composer::Project1Composer(Project* project): BaseProjectComposer(project) {}

Project* Project1Composer::createProject() {
    return Project::create("Project1Composer");
}

PatternSpace* Project1Composer::getBack() const {
    return project_->getPatterns()->at(0)->getSpace();
}

PatternSpace* Project1Composer::getFront() const {
    return project_->getPatterns()->at(1)->getSpace();
}

void Project1Composer::fillPatterns() {
    const auto patterns = project_->getPatterns();
    patterns->add(Pattern::create("Back"));
    patterns->add(Pattern::create("Front"));
}

void Project1Composer::fillParameters() {
    const auto parameters = project_->getParameters();
    parameters->add(Parameter::createDefault(ParameterName::BACK_WAIST_LENGTH, 42));
    parameters->add(Parameter::createDefault(ParameterName::BACK_WIDTH, 31));
    parameters->add(Parameter::createDefault(ParameterName::BUST_HEIGHT, 28));
    parameters->add(Parameter::createDefault(ParameterName::BUST_SPAN, 17));
    parameters->add(Parameter::createDefault(ParameterName::APEX_TO_CENTER_FRONT, 21));
    parameters->add(Parameter::createDefault(ParameterName::APEX_TO_SHOULDER, 27));
    parameters->add(Parameter::createDefault(ParameterName::HIP_DEPTH, 21.5));
    parameters->add(Parameter::createDefault(ParameterName::BUST_CIRCUMFERENCE, 96));
    parameters->add(Parameter::createDefault(ParameterName::WAIST_CIRCUMFERENCE, 68));
    parameters->add(Parameter::createDefault(ParameterName::NECK_CIRCUMFERENCE, 38));
    parameters->add(Parameter::createDefault(ParameterName::SHOULDER_LENGTH, 11));
    parameters->add(Parameter::createDefault(ParameterName::HIP_CIRCUMFERENCE, 98));
}

void Project1Composer::fillInstructions() {
    const auto back = getBack();
    const auto front = getFront();

    const auto space = project_->getSpace();
    const auto parameters = project_->getParameters();
    const auto instructions = project_->getInstructions();

    SelectedPatterns* selectedPatterns = nullptr;
    PatternInstructionsContainer* patternInstructions = nullptr;

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new FP(common, name(S), num(0.0), num(0.0)));
    patternInstructions->add(new RelP(use_last_point, name(W), down, param(BACK_WAIST_LENGTH)));
    patternInstructions->add(new RelP(use_last_point, name(H), down, param(HIP_DEPTH)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(H), pattern(back))), name(H1), right,
                                      biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Subtract())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(W), pattern(back))), name(W1), right,
                                      vecFunc(name(H), pattern(back), name(H1), pattern(back), new V::Length())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(W), pattern(back))), name(W2), right,
                                      biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Subtract())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(S), pattern(back))), name(S1), right,
                                      vecFunc(name(W), pattern(back), name(W2), pattern(back), new V::Length())));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(W), pattern(back))), name(AH), up,
                                      biFunc(vecFunc(name(S), pattern(back), name(W), pattern(back), new V::Length()),
                                             num(2), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(UB), up,
                                      biFunc(vecFunc(name(S), pattern(back), name(AH), pattern(back), new V::Length()),
                                             num(3), new B::Divide())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(H), pattern(back))), name(T), up,
                                      biFunc(vecFunc(name(H), pattern(back), name(W), pattern(back), new V::Length()),
                                             num(2), new B::Divide())));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(S), pattern(back))), name(N), right,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(N1), down,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(16), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(N2), left,
                                      vecFunc(name(N), pattern(back), name(S), pattern(back), new V::Length())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(N1), pattern(back))), name(N3), left,
                                      biFunc(vecFunc(name(N2), pattern(back), name(N1), pattern(back), new V::Length()),
                                             num(2), new B::Divide())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(N), pattern(back))), name(S2), num(-18), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(UB), pattern(back))), name(UB1), right,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(AH), pattern(back))), name(AH1), right,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(AH2), num(45), num(1.5)));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(AH), pattern(back))), name(AH3), right,
                                      vecFunc(name(W), pattern(back), name(W2), pattern(back), new V::Length())));
    patternInstructions->add(new RelP(use_last_point, name(AH4), left, num(1)));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(N), pattern(back))), name(D), num(-18),
                                      biFunc(vecFunc(name(N), pattern(back), name(S2), pattern(back), new V::Length()),
                                             num(2), new B::Divide())));

    patternInstructions->add(new D(common, name(N), name(S2), new Vec(new P(name(D), pattern(back)), num(90), num(7)), num(2), no_num));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(H), pattern(front))), name(H1), left,
                                      biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Add())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(W), pattern(front))), name(W1), left,
                                      vecFunc(name(H), pattern(front), name(H1), pattern(front), new V::Length())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(W), pattern(front))), name(W2), left,
                                      biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Add())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(S), pattern(front))), name(S1), left,
                                      vecFunc(name(W), pattern(front), name(W2), pattern(front), new V::Length())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(S), pattern(front))), name(N), left,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(N1), down,
                                      biFunc(biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide()),
                                             num(2), new B::Add())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(N), pattern(front))), name(S2), num(180 + 26), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(UB), pattern(front))), name(UB1), left,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide())));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(AH), pattern(front))), name(AH1), left,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(AH2), num(90 + 45), num(2.5)));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(AH), pattern(front))), name(AH3), left,
                                      vecFunc(name(W), pattern(front), name(W2), pattern(front), new V::Length())));
    patternInstructions->add(new RelP(use_last_point, name(AH4), right, num(1)));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(S), pattern(front))), name(B), down, param(BUST_HEIGHT)));
    patternInstructions->add(new RelP(use_last_point, name(DA), left,
                                      biFunc(param(BUST_SPAN), num(2), new B::Divide())));
    patternInstructions->add(new Adj(common, name(S2), new P(name(DA), pattern(front)), param(APEX_TO_SHOULDER), new P(name(N), pattern(front)), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelP(common, new OptionalArgument(new P(name(N), pattern(front))), name(D1),
                                      vecFunc(name(N), pattern(front), name(S2), pattern(front), new V::Angle()),
                                      biFunc(
                                          vecFunc(name(N), pattern(front), name(S2), pattern(front), new V::Length()),
                                          num(2), new B::Divide())));
    patternInstructions->add(new UD(common, name(N), name(S2), name(DA), name(D1),
                                    biFunc(biFunc(biFunc(
                                                   param(BUST_CIRCUMFERENCE), num(20), new B::Divide()),
                                               num(1), new B::Add()),
                                           num(2), new B::Multiply())
    ));
    patternInstructions->add(new IP(common, name(UB1_1), name(UB), name(UB1), name(D1), name(DA)));
    patternInstructions->add(new IP(common, name(UB1_2), name(UB), name(UB1), name(D1_1), name(DA)));
    patternInstructions->add(new IP(common, name(AH1_1), name(AH), name(AH1), name(D1), name(DA)));
    patternInstructions->add(new IP(common, name(AH1_2), name(AH), name(AH1), name(D1_1), name(DA)));
    patternInstructions->add(new MP(common, name(UB1),
                                    vecFunc(name(UB1_1), pattern(front), name(UB1_2), pattern(front), new V::Angle()),
                                    vecFunc(name(UB1_1), pattern(front), name(UB1_2), pattern(front), new V::Length()))
    );
    patternInstructions->add(new MP(common, name(AH1),
                                    vecFunc(name(AH1_1), pattern(front), name(AH1_2), pattern(front), new V::Angle()),
                                    vecFunc(name(AH1_1), pattern(front), name(AH1_2), pattern(front), new V::Length()))
    );
    patternInstructions->add(new MP(common, name(AH3),
                                    vecFunc(name(AH1_1), pattern(front), name(AH1_2), pattern(front), new V::Angle()),
                                    vecFunc(name(AH1_1), pattern(front), name(AH1_2), pattern(front), new V::Length()))
    );
    patternInstructions->add(new MP(common, name(AH4),
                                    vecFunc(name(AH1_1), pattern(front), name(AH1_2), pattern(front), new V::Angle()),
                                    vecFunc(name(AH1_1), pattern(front), name(AH1_2), pattern(front), new V::Length()))
    );

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(AH3)));
    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(H1)));
    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(H)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(UB)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(N2)));
    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(N)));
}
