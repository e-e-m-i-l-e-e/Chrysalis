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

    args::patterns* patterns = nullptr;
    PatternInstructionsContainer* patternInstructions = nullptr;

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new FP(common, name(S), num(0.0), num(0.0)));
    patternInstructions->add(new RelP(use_last_point, name(W), down, param(BACK_WAIST_LENGTH)));
    patternInstructions->add(new RelP(use_last_point, name(H), down, param(HIP_DEPTH)));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, new OptionalArgument(point(H)), name(H1), right,
                                      biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Subtract())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(W)), name(W1), right,
                                      vecFunc(point(H), point(H1), new V::Length())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(W)), name(W2), right,
                                      biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Subtract())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(S)), name(S1), right,
                                      vecFunc(point(W), point(W2), new V::Length())));

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, new OptionalArgument(point(W)), name(AH), up,
                                      biFunc(vecFunc(point(S), point(W), new V::Length()),
                                             num(2), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(UB), up,
                                      biFunc(vecFunc(point(S), point(AH), new V::Length()),
                                             num(3), new B::Divide())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(H)), name(T), up,
                                      biFunc(vecFunc(point(H), point(W), new V::Length()),
                                             num(2), new B::Divide())));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, new OptionalArgument(point(S)), name(N), right,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(N1), down,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(16), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(N2), left,
                                      vecFunc(point(N), point(S), new V::Length())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(N1)), name(N3), left,
                                      biFunc(vecFunc(point(N2), point(N1), new V::Length()),
                                             num(2), new B::Divide())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(N)), name(S2), num(-18), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(UB)), name(UB1), right,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(AH)), name(AH1), right,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(AH2), num(45), num(1.5)));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(AH)), name(AH3), right,
                                      vecFunc(point(W), point(W2), new V::Length())));
    patternInstructions->add(new RelP(use_last_point, name(AH4), left, num(1)));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(N)), name(D), num(-18),
                                      biFunc(vecFunc(point(N), point(S2), new V::Length()),
                                             num(2), new B::Divide())));

    patternInstructions->add(new D(common, name(N), name(S2), new Vec(point(D), num(90), num(7)), num(2), no_num));

    patterns = new args::patterns();
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, new OptionalArgument(point(H)), name(H1), left,
                                      biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Add())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(W)), name(W1), left,
                                      vecFunc(point(H), point(H1), new V::Length())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(W)), name(W2), left,
                                      biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Add())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(S)), name(S1), left,
                                      vecFunc(point(W), point(W2), new V::Length())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(S)), name(N), left,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(N1), down,
                                      biFunc(biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide()),
                                             num(2), new B::Add())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(N)), name(S2), num(180 + 26), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(UB)), name(UB1), left,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide())));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(AH)), name(AH1), left,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide())));
    patternInstructions->add(new RelP(use_last_point, name(AH2), num(90 + 45), num(2.5)));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(AH)), name(AH3), left,
                                      vecFunc(point(W), point(W2), new V::Length())));
    patternInstructions->add(new RelP(use_last_point, name(AH4), right, num(1)));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(S)), name(B), down, param(BUST_HEIGHT)));
    patternInstructions->add(new RelP(use_last_point, name(DA), left,
                                      biFunc(param(BUST_SPAN), num(2), new B::Divide())));
    patternInstructions->add(new Adj(common, name(S2), point(DA), param(APEX_TO_SHOULDER), point(N), param(SHOULDER_LENGTH)));
    patternInstructions->add(new RelP(common, new OptionalArgument(point(N)), name(D1),
                                      vecFunc(point(N), point(S2), new V::Angle()),
                                      biFunc(
                                          vecFunc(point(N), point(S2), new V::Length()),
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
                                    vecFunc(point(UB1_1), point(UB1_2), new V::Angle()),
                                    vecFunc(point(UB1_1), point(UB1_2), new V::Length()))
    );
    patternInstructions->add(new MP(common, name(AH1),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Angle()),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Length()))
    );
    patternInstructions->add(new MP(common, name(AH3),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Angle()),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Length()))
    );
    patternInstructions->add(new MP(common, name(AH4),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Angle()),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Length()))
    );

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(AH3)));
    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(H1)));
    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(H)));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(UB)));

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(N2)));
    patternInstructions->add(new BuildOutlineInstruction(common, no_name, name(N)));
}
