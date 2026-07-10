#include "Project1Composer.h"

#include "instructions.h"
#include "instructions/BuildOutlineInstruction.h"

#include "arguments/ComparisonArgument.h"
#include "arguments/ParameterArgument.h"
#include "instructions/ConditionalInstructionsContainer.h"
#include "instructions/CurveInstruction.h"
#include "instructions/ExpressionInstruction.h"
#include "instructions/PatternInstructionsContainer.h"

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

void Project1Composer::fillOptions() {
    const auto options = project_->getInstructions()->options();
    options->add(Option::createDefault(Options::HAS_CENTER_BACK_DART, true));
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
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new FP(common, name(S), num(0.0), num(0.0)));
    patternInstructions->add(new RelP(common, name(W), vector_0(down, param(BACK_WAIST_LENGTH))));
    patternInstructions->add(new RelP(common, name(H), vector_0(down, param(HIP_DEPTH))));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, name(H1), vector_(H, right,
                                      *(*param(HIP_CIRCUMFERENCE) / *num(4)) - *num(1)),
                                      new args::optional<args::line>()));
    patternInstructions->add(new RelP(common, name(W1), vector_(W, right,
                                      vecFunc(Length, point(H), point(H1)))));
    patternInstructions->add(new RelP(common, name(W2), vector_(W, right,
                                      *(*param(BUST_CIRCUMFERENCE) / *num(4)) - *num(1)),
                                      new args::optional<args::line>()));
    patternInstructions->add(new RelP(common, name(S1), vector_(S, right,
                                      vecFunc(Length, point(W), point(W2)))));

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, name(AH), vector_(W, up,
                                      *vecFunc(Length, point(S), point(W)) / *num(2))));
    patternInstructions->add(new RelP(common, name(UB), vector_0(up,
                                      *vecFunc(Length, point(S), point(AH)) / *num(3)),
                                      new args::optional<args::line>()));
    patternInstructions->add(new RelP(common, name(T), vector_(H, up,
                                      *vecFunc(Length, point(H), point(W)) / *num(2)),
                                      new args::optional<args::line>()));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new RelP(common, name(N), vector_(S, right, *param(NECK_CIRCUMFERENCE) / *num(6))));
    patternInstructions->add(new RelP(common, name(N1), vector_0(down,
                                      *param(NECK_CIRCUMFERENCE) / *num(16))));
    patternInstructions->add(new RelP(common, name(N2), vector_0(left,
                                      vecFunc(Length, point(N), point(S)))));
    patternInstructions->add(new RelP(common, name(N3), vector_(N1, left,
                                      *vecFunc(Length, point(N2), point(N1)) / *num(2)),
                                             new args::optional<args::line>()));
    patternInstructions->add(new RelP(common, name(S2), vector_(N, num(-18), param(SHOULDER_LENGTH))));
    patternInstructions->add(new RelP(common, name(UB1), vector_(UB, right,
                                      *param(BACK_WIDTH) / *num(2))));
    patternInstructions->add(new RelP(common, name(AH1), vector_(AH, right,
                                      *param(BACK_WIDTH) / *num(2))));
    patternInstructions->add(new RelP(common, name(AH2), vector_0(num(45), num(1.5))));
    patternInstructions->add(new RelP(common, name(AH3), vector_(AH, right,
                                      vecFunc(Length, point(W), point(W2)))));
    patternInstructions->add(new RelP(common, name(AH4), vector_0(left, num(1))));
    patternInstructions->add(new RelP(common, name(D), vector_(N, num(-18),
                                      *vecFunc(Length, point(N), point(S2)) / *num(2)),
                                      new args::optional<args::line>()));

    patternInstructions->add(new D(common, segment(N, S2), new Vec(point(D), num(90), num(7)), num(2), no_num));

    instructions->add(new ExpressionInstruction(project_->getInstructions()->expressions(),
                                                new args::expr(Expressions::INTAKE, *param(BUST_CIRCUMFERENCE) + *param(HIP_CIRCUMFERENCE))));
    instructions->add(new ExpressionInstruction(project_->getInstructions()->expressions(),
                                                new args::expr(Expressions::MAX_INTAKE, *(*num(2) + *num(4)) + *(new args::conditional(option(HAS_CENTER_BACK_DART), num(2), num(0))))));

    const auto positive = new BaseInstructionsContainer<BaseInstruction>(project_->getInstructions()->options(), project_->getInstructions()->expressions());
    const auto negative = new BaseInstructionsContainer<BaseInstruction>(project_->getInstructions()->options(), project_->getInstructions()->expressions());
    instructions->add(new ConditionalInstructionsContainer(new args::compare::Less(expression(MAX_INTAKE), expression(INTAKE)), positive, negative));

    positive->add(new ExpressionInstruction(project_->getInstructions()->expressions(),
        new args::expr(Expressions::COEFFICIENT, biFunc(Min, num(1), *expression(INTAKE) / *(*expression(MAX_INTAKE) + *(*(*num(2) / *num(3)) * *num(2)))))));

    negative->add(new ExpressionInstruction(project_->getInstructions()->expressions(),
        new args::expr(Expressions::COEFFICIENT, *expression(INTAKE) / *expression(MAX_INTAKE))));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, name(W3), vector_(W, right, *num(2) * *expression(COEFFICIENT))));
    patternInstructions->add(new RelP(common, name(W4), vector_(W2, left, *num(4) * *expression(COEFFICIENT))));

    patterns = new args::patterns();
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new RelP(common, name(H1), vector_(H, left,
                                      *(*param(HIP_CIRCUMFERENCE) / *num(4)) + *num(1)),
                                      new args::optional<args::line>()));
    patternInstructions->add(new RelP(common, name(W1), vector_(W, left,
                                      vecFunc(Length, point(H), point(H1)))));
    patternInstructions->add(new RelP(common, name(W2), vector_(W, left,
                                      *(*param(BUST_CIRCUMFERENCE) / *num(4)) + *num(1)),
                                             new args::optional<args::line>()));
    patternInstructions->add(new RelP(common, name(S1), vector_(S, left,
                                      vecFunc(Length, point(W), point(W2)))));
    patternInstructions->add(new RelP(common, name(N), vector_(S, left,
                                      *param(NECK_CIRCUMFERENCE) / *num(6))));
    patternInstructions->add(new RelP(common, name(N1), vector_0(down,
                                      *(*param(NECK_CIRCUMFERENCE) / *num(6)) + *num(2)),
                                      new args::optional<args::line>()));
    patternInstructions->add(new RelP(common, name(S2), vector_(N, num(180 + 26), param(SHOULDER_LENGTH))));
    patternInstructions->add(new RelP(common, name(UB1), vector_(UB, left,
                                      *param(BACK_WIDTH) / *num(2))));
    patternInstructions->add(new RelP(common, name(AH1), vector_(AH, left,
                                      *param(BACK_WIDTH) / *num(2))));
    patternInstructions->add(new RelP(common, name(AH2), vector_0(num(90 + 45), num(2.5))));
    patternInstructions->add(new RelP(common, name(AH3), vector_(AH, left,
                                      vecFunc(Length, point(W), point(W2)))));
    patternInstructions->add(new RelP(common, name(AH4), vector_0(right, num(1))));
    patternInstructions->add(new RelP(common, name(B), vector_(S, down, param(BUST_HEIGHT))));
    patternInstructions->add(new RelP(common, name(DA), vector_0(left,
                                      *param(BUST_SPAN) / *num(2))));
    patternInstructions->add(new RelP(common, name(N2), vector_(DA, num(0), param(APEX_TO_CENTER_FRONT)), new args::optional<args::line>(segment(H, S))));
    patternInstructions->add(new RelP(common, name(N1), vector_0(left, vecFunc(Length, point(S), point(N)))));
    patternInstructions->add(new RelP(common, name(N3), vector_(N, down, *vecFunc(Length, point(N1), point(N)) / *num(3))));
    patternInstructions->add(new RelP(common, name(N4), vector_(N2, left, *vecFunc(Length, point(N1), point(N2)) / *num(3))));
    patternInstructions->add(new MP(common, point(S2), vector_no_angle(DA, param(APEX_TO_SHOULDER)), new args::optional(vector_no_angle(N, param(SHOULDER_LENGTH)))));
    patternInstructions->add(new RelP(common, name(D1),
                                      vector_(N, vecFunc(Angle, point(N), point(S2)),
                                      *vecFunc(Length, point(N), point(S2)) / *num(2)),
                                      new args::optional<args::line>()));
    patternInstructions->add(new UD(common, segment(N, S2), segment(D1, DA),
                                    *(*(*param(BUST_CIRCUMFERENCE) / *num(20)) + *num(1)) * *num(2))
    );
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

    patternInstructions->add(new MP(common, point(UB1), vector_0(
                                    vecFunc(Angle, point(UB1_1), point(UB1_2)),
                                    vecFunc(Length, point(UB1_1), point(UB1_2))),
                                    new args::optional<args::vector>())
    );
    patternInstructions->add(new MP(common, point(AH1), vector_0(
                                    vecFunc(Angle, point(AH1_1), point(AH1_2)),
                                    vecFunc(Length, point(AH1_1), point(AH1_2))),
                                    new args::optional<args::vector>())
    );
    patternInstructions->add(new MP(common, point(AH3), vector_0(
                                    vecFunc(Angle, point(AH1_1), point(AH1_2)),
                                    vecFunc(Length, point(AH1_1), point(AH1_2))),
                                    new args::optional<args::vector>())
    );
    patternInstructions->add(new MP(common, point(AH4), vector_0(
                                    vecFunc(Angle, point(AH1_1), point(AH1_2)),
                                    vecFunc(Length, point(AH1_1), point(AH1_2))),
                                    new args::optional<args::vector>())
    );
    patternInstructions->add(new CurveInstruction(common, segment(N, N3), segment(N2, N4), new args::container<PatternPointArgument>()));

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(AH3)));
    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(H1)));
    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(H)));

    patterns = new args::patterns();
    patterns->add(back);
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);
    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(UB)));

    patterns = new args::patterns();
    patterns->add(back);
    patterns->add(front);
    patternInstructions = new PatternInstructionsContainer(project_->getInstructions()->options(), project_->getInstructions()->expressions(), patterns);
    instructions->add(patternInstructions);

    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(N2)));
    patternInstructions->add(new BuildOutlineInstruction(common, new Argument<std::string>("main"), name(N)));
}
