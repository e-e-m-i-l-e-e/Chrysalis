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
    return (*project_->getPatterns())[0]->getSpace();
}

PatternSpace* Project1Composer::getFront() const {
    return (*project_->getPatterns())[1]->getSpace();
}

void Project1Composer::fillPatterns() {
    const auto patterns = project_->getPatterns();
    auto back = Pattern::create("Back");
    back->getSpace()->getOutline()->add(new Outline("main"));
    auto front = Pattern::create("Front");
    front->getSpace()->getOutline()->add(new Outline("main"));
    patterns->add(back);
    patterns->add(front);
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
    patternInstructions->add(new RelP(use_last_point, name(W), vector_0(down, param(BACK_WAIST_LENGTH))));
    patternInstructions->add(new RelP(use_last_point, name(H), vector_0(down, param(HIP_DEPTH))));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(H)), name(H1), vector_0(right,
                                      biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Subtract()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(W)), name(W1), vector_0(right,
                                      vecFunc(point(H), point(H1), new V::Length()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(W)), name(W2), vector_0(right,
                                      biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Subtract()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(S)), name(S1), vector_0(right,
                                      vecFunc(point(W), point(W2), new V::Length()))));

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(W)), name(AH), vector_0(up,
                                      biFunc(vecFunc(point(S), point(W), new V::Length()),
                                             num(2), new B::Divide()))));
    patternInstructions->add(new RelP(use_last_point, name(UB), vector_0(up,
                                      biFunc(vecFunc(point(S), point(AH), new V::Length()),
                                             num(3), new B::Divide()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(H)), name(T), vector_0(up,
                                      biFunc(vecFunc(point(H), point(W), new V::Length()),
                                             num(2), new B::Divide()))));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(S)), name(N), vector_0(right,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide()))));
    patternInstructions->add(new RelP(use_last_point, name(N1), vector_0(down,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(16), new B::Divide()))));
    patternInstructions->add(new RelP(use_last_point, name(N2), vector_0(left,
                                      vecFunc(point(N), point(S), new V::Length()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(N1)), name(N3), vector_0(left,
                                      biFunc(vecFunc(point(N2), point(N1), new V::Length()),
                                             num(2), new B::Divide()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(N)), name(S2), vector_0(num(-18), param(SHOULDER_LENGTH))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(UB)), name(UB1), vector_0(right,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(AH)), name(AH1), vector_0(right,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide()))));
    patternInstructions->add(new RelP(use_last_point, name(AH2), vector_0(num(45), num(1.5))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(AH)), name(AH3), vector_0(right,
                                      vecFunc(point(W), point(W2), new V::Length()))));
    patternInstructions->add(new RelP(use_last_point, name(AH4), vector_0(left, num(1))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(N)), name(D), vector_0(num(-18),
                                      biFunc(vecFunc(point(N), point(S2), new V::Length()),
                                             num(2), new B::Divide()))));

    patternInstructions->add(new D(common, segment(N, S2), new Vec(point(D), num(90), num(7)), num(2), no_num));

    patterns = new args::patterns();
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(H)), name(H1), vector_0(left,
                                      biFunc(biFunc(param(HIP_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Add()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(W)), name(W1), vector_0(left,
                                      vecFunc(point(H), point(H1), new V::Length()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(W)), name(W2), vector_0(left,
                                      biFunc(biFunc(param(BUST_CIRCUMFERENCE), num(4), new B::Divide()),
                                             num(1), new B::Add()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(S)), name(S1), vector_0(left,
                                      vecFunc(point(W), point(W2), new V::Length()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(S)), name(N), vector_0(left,
                                      biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide()))));
    patternInstructions->add(new RelP(use_last_point, name(N1), vector_0(down,
                                      biFunc(biFunc(param(NECK_CIRCUMFERENCE), num(6), new B::Divide()),
                                             num(2), new B::Add()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(N)), name(S2), vector_0(num(180 + 26), param(SHOULDER_LENGTH))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(UB)), name(UB1), vector_0(left,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide()))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(AH)), name(AH1), vector_0(left,
                                      biFunc(param(BACK_WIDTH), num(2), new B::Divide()))));
    patternInstructions->add(new RelP(use_last_point, name(AH2), vector_0(num(90 + 45), num(2.5))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(AH)), name(AH3), vector_0(left,
                                      vecFunc(point(W), point(W2), new V::Length()))));
    patternInstructions->add(new RelP(use_last_point, name(AH4), vector_0(right, num(1))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(S)), name(B), vector_0(down, param(BUST_HEIGHT))));
    patternInstructions->add(new RelP(use_last_point, name(DA), vector_0(left,
                                      biFunc(param(BUST_SPAN), num(2), new B::Divide()))));
    patternInstructions->add(new Adj(common, point(S2), vector_no_angle(DA, param(APEX_TO_SHOULDER)), vector_no_angle(N, param(SHOULDER_LENGTH))));
    patternInstructions->add(new RelP(common, new OptionalArgument<args::point>(point(N)), name(D1),
                                      vector_0(vecFunc(point(N), point(S2), new V::Angle()),
                                      biFunc(
                                          vecFunc(point(N), point(S2), new V::Length()),
                                          num(2), new B::Divide()))));
    patternInstructions->add(new UD(common, segment(N, S2), segment(D1, DA),
                                    biFunc(biFunc(biFunc(
                                                   param(BUST_CIRCUMFERENCE), num(20), new B::Divide()),
                                               num(1), new B::Add()),
                                           num(2), new B::Multiply())
    ));
    auto segments = new args::container<args::line>();
    segments->add(segment(D1, DA));
    segments->add(segment(D1_1, DA));
    auto names = new args::container<args::name>();
    names->add(name(UB1_1));
    names->add(name(UB1_2));
    patternInstructions->add(new IP(common, segment(UB, UB1), names, segments));

    segments = new args::container<args::line>();
    segments->add(segment(D1, DA));
    segments->add(segment(D1_1, DA));
    names = new args::container<args::name>();
    names->add(name(AH1_1));
    names->add(name(AH1_2));
    patternInstructions->add(new IP(common, segment(AH, AH1), names, segments));

    patternInstructions->add(new MP(common, vector_(UB1,
                                    vecFunc(point(UB1_1), point(UB1_2), new V::Angle()),
                                    vecFunc(point(UB1_1), point(UB1_2), new V::Length())))
    );
    patternInstructions->add(new MP(common, vector_(AH1,
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Angle()),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Length())))
    );
    patternInstructions->add(new MP(common, vector_(AH3,
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Angle()),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Length())))
    );
    patternInstructions->add(new MP(common, vector_(AH4,
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Angle()),
                                    vecFunc(point(AH1_1), point(AH1_2), new V::Length())))
    );

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(AH3)));
    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(H1)));
    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(H)));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(UB)));

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(N2)));
    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(N)));
}
