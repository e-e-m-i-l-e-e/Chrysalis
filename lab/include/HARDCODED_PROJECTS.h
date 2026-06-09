#ifndef CHRYSALIS_HARDCODED_PROJECTS_H
#define CHRYSALIS_HARDCODED_PROJECTS_H

#include "Project.h"
#include "arguments/ParameterArgument.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/RelativePointInstruction.h"

namespace Chrysalis {
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

    inline void setupProject1(const Project* project) {
        const auto parameters = project->getParameters();
        const auto backWaistLength = new Parameter(BACK_WAIST_LENGTH);
        backWaistLength->setValue(42);
        parameters->add(backWaistLength);

        const auto backWidth = new Parameter(BACK_WIDTH);
        backWidth->setValue(31);
        parameters->add(backWidth);

        const auto bustHeight = new Parameter(BUST_HEIGHT);
        bustHeight->setValue(28);
        parameters->add(bustHeight);

        const auto bustSpan = new Parameter(BUST_SPAN);
        bustSpan->setValue(17);
        parameters->add(bustSpan);

        const auto apexToCenterFront = new Parameter(APEX_TO_CENTER_FRONT);
        apexToCenterFront->setValue(21);
        parameters->add(apexToCenterFront);

        const auto apexToShoulder = new Parameter(APEX_TO_SHOULDER);
        apexToShoulder->setValue(27);
        parameters->add(apexToShoulder);

        const auto hipDepth = new Parameter(HIP_DEPTH);
        hipDepth->setValue(21.5);
        parameters->add(hipDepth);

        const auto bustCircumference = new Parameter(BUST_CIRCUMFERENCE);
        bustCircumference->setValue(96);
        parameters->add(bustCircumference);

        const auto waistCircumference = new Parameter(WAIST_CIRCUMFERENCE);
        waistCircumference->setValue(68);
        parameters->add(waistCircumference);

        const auto neckCircumference = new Parameter(NECK_CIRCUMFERENCE);
        neckCircumference->setValue(38);
        parameters->add(neckCircumference);

        const auto shoulderLength = new Parameter(SHOULDER_LENGTH);
        shoulderLength->setValue(11);
        parameters->add(shoulderLength);

        const auto hipCircumference = new Parameter(HIP_CIRCUMFERENCE);
        hipCircumference->setValue(98);
        parameters->add(hipCircumference);

        const auto backPatternSpace = new PatternSpace(new OutlineContainer());
        const auto frontPatternSpace = new PatternSpace(new OutlineContainer());

        project->getPatterns()->add(new Pattern("Back", backPatternSpace));
        project->getPatterns()->add(new Pattern("Front", frontPatternSpace));

        auto selectedPatterns = new SelectedPatterns();
        selectedPatterns->add(backPatternSpace);
        selectedPatterns->add(frontPatternSpace);
        auto instructions = new PatternInstructionsContainer(selectedPatterns);
        instructions->add(new FreePointInstruction(project->getSpace(), new SelectedPatternsArgument(selectedPatterns), new NameArgument("A"), new NumberArgument(0), new NumberArgument(0)));
        instructions->add(new RelativePointInstruction(project->getSpace(), new SelectedPatternsArgument(selectedPatterns), new NameArgument(), new PatternArgument(), new NameArgument("B"), new NumberArgument(270), new ParameterArgument(parameters->get(BACK_WAIST_LENGTH))));
        project->getInstructions()->add(instructions);

        selectedPatterns = new SelectedPatterns();
        selectedPatterns->add(backPatternSpace);
        instructions = new PatternInstructionsContainer(selectedPatterns);
        instructions->add(new RelativePointInstruction(project->getSpace(), new SelectedPatternsArgument(selectedPatterns), new NameArgument(), new PatternArgument(), new NameArgument("C"), new NumberArgument(0), new NumberArgument(10)));
        project->getInstructions()->add(instructions);

        selectedPatterns = new SelectedPatterns();
        selectedPatterns->add(frontPatternSpace);
        instructions = new PatternInstructionsContainer(selectedPatterns);
        instructions->add(new RelativePointInstruction(project->getSpace(), new SelectedPatternsArgument(selectedPatterns), new NameArgument(), new PatternArgument(), new NameArgument("D"), new NumberArgument(180), new NumberArgument(20)));
        project->getInstructions()->add(instructions);
    }
}

#endif //CHRYSALIS_HARDCODED_PROJECTS_H