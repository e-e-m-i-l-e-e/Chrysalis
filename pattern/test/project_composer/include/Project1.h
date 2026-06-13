#ifndef CHRYSALIS_PROJECT1_H
#define CHRYSALIS_PROJECT1_H

#include "BaseProject.h"

namespace Chrysalis {
    class Project1 : public BaseProject {
        struct PointName {
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
        };
        struct ParameterName {
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
        };
    public:
        void fillPatterns(Project* project) override;
        void fillParameters(Project* project) override;
        void fillInstructions(Project* project) override;
    };
}

#endif //CHRYSALIS_PROJECT1_H