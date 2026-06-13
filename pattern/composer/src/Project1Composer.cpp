#include "Project1Composer.h"

#include "instructions.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/RelativePointInstruction.h"
#include "instructions/BuildOutlineInstruction.h"

#include "arguments/ParameterArgument.h"
#include "arguments/BinaryFunctionArgument.h"
#include "arguments/VectorFunctionArgument.h"

using namespace Chrysalis;

Project* Project1Composer::create() const {
    return Project::create("Project1Composer");
}

void Project1Composer::fillPatterns(Project* project) {
    const auto patterns = project->getPatterns();
    patterns->add(Pattern::create("Back"));
    patterns->add(Pattern::create("Front"));
}

void Project1Composer::fillParameters(Project* project) {
    const auto parameters = project->getParameters();
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

void Project1Composer::fillInstructions(Project* project) {
    const auto space = project->getSpace();
    const auto parameters = project->getParameters();
    const auto instructions = project->getInstructions();
    const auto back = project->getPatterns()->at(0)->getSpace();
    const auto front = project->getPatterns()->at(1)->getSpace();
    
    SelectedPatterns* selectedPatterns = nullptr;
    PatternInstructionsContainer* patternInstructions = nullptr;

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new FreePointInstruction(common, name(S), num(0.0), num(0.0)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(W), down, param(BACK_WAIST_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(H), down, param(HIP_DEPTH)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelativePointInstruction(common, name(H), pattern(), name(H1), right,
                                                          biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::subtract)));
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(W1), right,
                                                          vecFunc(name(H), pattern(back), name(H1), pattern(back), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(W2), right,
                                                          biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::subtract)));
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(S1), right,
                                                      vecFunc(name(W), pattern(back), name(W2), pattern(back), &VectorFunction::length)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(AH), up,
                                                          biFunc(vecFunc(name(S), pattern(back), name(W), pattern(back), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(UB), up,
                                                      biFunc(vecFunc(name(S), pattern(back), name(AH), pattern(back), &VectorFunction::length),
                                                          num(3), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name(H), pattern(), name(T), up,
                                                  biFunc(vecFunc(name(H), pattern(back), name(W), pattern(back), &VectorFunction::length),
                                                      num(2), &BinaryFunction::divide)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(back);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(N), right,
                                                          biFunc(param(NECK_CIRCUMFERENCE), num(6), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(N1), down,
                                                      biFunc(param(NECK_CIRCUMFERENCE), num(16), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(N2), left,
                                                          vecFunc(name(N), pattern(back), name(S), pattern(back), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name(N1), pattern(), name(N3), left,
                                                          biFunc(vecFunc(name(N2), pattern(back), name(N1), pattern(back), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name(N), pattern(), name(S2), num(-18), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelativePointInstruction(common, name(UB), pattern(), name(UB1), right,
                                                          biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(common, name(AH), pattern(), name(AH1), right,
                                                      biFunc(param(BACK_WIDTH), num(2), &BinaryFunction::divide)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(AH2), num(45), num(1.5)));
    patternInstructions->add(new RelativePointInstruction(common, name(AH), pattern(), name(AH3), right,
                                                      vecFunc(name(W), pattern(back), name(W2), pattern(back), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(AH4), left, num(1)));
    patternInstructions->add(new RelativePointInstruction(common, name(N), pattern(), name(D), num(-18),
                                                          biFunc(vecFunc(name(N), pattern(back), name(S2), pattern(back), &VectorFunction::length),
                                                              num(2), &BinaryFunction::divide)));

    selectedPatterns = new SelectedPatterns();
    selectedPatterns->add(front);
    patternInstructions = new PatternInstructionsContainer(selectedPatterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelativePointInstruction(common, name(H), pattern(), name(H1), left,
                                                          biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::add)));
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(W1), left,
                                                          vecFunc(name(H), pattern(front), name(H1), pattern(front), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(common, name(W), pattern(), name(W2), left,
                                                          biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), &BinaryFunction::divide),
                                                              num(1), &BinaryFunction::add)));
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(S1), left,
                                                          vecFunc(name(W), pattern(front), name(W2), pattern(front), &VectorFunction::length)));
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
                                                          vecFunc(name(W), pattern(front), name(W2), pattern(front), &VectorFunction::length)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(AH4), right, num(1)));
    patternInstructions->add(new RelativePointInstruction(common, name(S), pattern(), name(B), down, param(BUST_HEIGHT)));
    patternInstructions->add(new RelativePointInstruction(use_last_point, name(DA), left,
                                                          biFunc(param(BUST_SPAN), num(2), &BinaryFunction::divide)));

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
