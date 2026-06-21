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

    patternInstructions->add(new P(common, name(S), num(0.0), num(0.0)));
    patternInstructions->add(new RelP(use_last_point, name(W), down, param(BACK_WAIST_LENGTH)));
    patternInstructions->add(new RelP(use_last_point, name(H), down, param(HIP_DEPTH)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, name(H), pattern(), name(H1), right,
                                      biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), &B::divide),
                                             num(1), &B::subtract)));
    patternInstructions->add(new RelP(common, name(W), pattern(), name(W1), right,
                                      vecFunc(name(H), pattern(back), name(H1), pattern(back), &V::length)));
    patternInstructions->add(new RelP(common, name(W), pattern(), name(W2), right,
                                      biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), &B::divide),
                                             num(1), &B::subtract)));
    patternInstructions->add(new RelP(common, name(S), pattern(), name(S1), right,
                                      vecFunc(name(W), pattern(back), name(W2), pattern(back), &V::length)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, name(W), pattern(), name(AH), up,
                                      biFunc(vecFunc(name(S), pattern(back), name(W), pattern(back), &V::length),
                                             num(2), &B::divide)));
    patternInstructions->add(new RelP(use_last_point, name(UB), up,
                                      biFunc(vecFunc(name(S), pattern(back), name(AH), pattern(back), &V::length),
                                             num(3), &B::divide)));
    patternInstructions->add(new RelP(common, name(H), pattern(), name(T), up,
                                      biFunc(vecFunc(name(H), pattern(back), name(W), pattern(back), &V::length),
                                             num(2), &B::divide)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, name(S), pattern(), name(N), right,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(6), &B::divide)));
    patternInstructions->add(new RelP(use_last_point, name(N1), down,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(16), &B::divide)));
    patternInstructions->add(new RelP(use_last_point, name(N2), left,
                                      vecFunc(name(N), pattern(back), name(S), pattern(back), &V::length)));
    patternInstructions->add(new RelP(common, name(N1), pattern(), name(N3), left,
                                      biFunc(vecFunc(name(N2), pattern(back), name(N1), pattern(back), &V::length),
                                             num(2), &B::divide)));
    patternInstructions->add(new RelP(common, name(N), pattern(), name(S2), num(-18), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelP(common, name(UB), pattern(), name(UB1), right,
                                      biFunc(param(BACK_WIDTH), num(2), &B::divide)));
    patternInstructions->add(new RelP(common, name(AH), pattern(), name(AH1), right,
                                      biFunc(param(BACK_WIDTH), num(2), &B::divide)));
    patternInstructions->add(new RelP(use_last_point, name(AH2), num(45), num(1.5)));
    patternInstructions->add(new RelP(common, name(AH), pattern(), name(AH3), right,
                                      vecFunc(name(W), pattern(back), name(W2), pattern(back), &V::length)));
    patternInstructions->add(new RelP(use_last_point, name(AH4), left, num(1)));
    patternInstructions->add(new RelP(common, name(N), pattern(), name(D), num(-18),
                                      biFunc(vecFunc(name(N), pattern(back), name(S2), pattern(back), &V::length),
                                             num(2), &B::divide)));

    patternInstructions->add(new D(common, name(N), name(S2), name(D), num(), num(7), num(2), num()));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, name(H), pattern(), name(H1), left,
                                      biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), &B::divide),
                                             num(1), &B::add)));
    patternInstructions->add(new RelP(common, name(W), pattern(), name(W1), left,
                                      vecFunc(name(H), pattern(front), name(H1), pattern(front), &V::length)));
    patternInstructions->add(new RelP(common, name(W), pattern(), name(W2), left,
                                      biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), &B::divide),
                                             num(1), &B::add)));
    patternInstructions->add(new RelP(common, name(S), pattern(), name(S1), left,
                                      vecFunc(name(W), pattern(front), name(W2), pattern(front), &V::length)));
    patternInstructions->add(new RelP(common, name(S), pattern(), name(N), left,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(6), &B::divide)));
    patternInstructions->add(new RelP(use_last_point, name(N1), down,
                                      biFunc(biFunc(param(NECK_CIRCUMFERENCE), num(6), &B::divide),
                                             num(2), &B::add)));
    patternInstructions->add(new RelP(common, name(N), pattern(), name(S2), num(180 + 26), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelP(common, name(UB), pattern(), name(UB1), left,
                                      biFunc(param(BACK_WIDTH), num(2), &B::divide)));
    patternInstructions->add(new RelP(common, name(AH), pattern(), name(AH1), left,
                                      biFunc(param(BACK_WIDTH), num(2), &B::divide)));
    patternInstructions->add(new RelP(use_last_point, name(AH2), num(90 + 45), num(2.5)));
    patternInstructions->add(new RelP(common, name(AH), pattern(), name(AH3), left,
                                      vecFunc(name(W), pattern(front), name(W2), pattern(front), &V::length)));
    patternInstructions->add(new RelP(use_last_point, name(AH4), right, num(1)));
    patternInstructions->add(new RelP(common, name(S), pattern(), name(B), down, param(BUST_HEIGHT)));
    patternInstructions->add(new RelP(use_last_point, name(DA), left,
                                      biFunc(param(BUST_SPAN), num(2), &B::divide)));

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
