#ifndef CHRYSALIS_PROJECT1_H
#define CHRYSALIS_PROJECT1_H

#include "BaseProjectComposer.h"

namespace Chrysalis {
    class Project1Composer: public BaseProjectComposer {
        struct PointName {
            static constexpr auto S = "S";
            static constexpr auto S1 = "S1";
            static constexpr auto S2 = "S2";

            static constexpr auto N = "N";
            static constexpr auto N1 = "N1";
            static constexpr auto N2 = "N2";
            static constexpr auto N3 = "N3";
            static constexpr auto N4 = "N4";

            static constexpr auto AH = "AH";
            static constexpr auto AH1 = "AH1";
            static constexpr auto AH2 = "AH2";
            static constexpr auto AH3 = "AH3";
            static constexpr auto AH4 = "AH4";
            static constexpr auto AH1_1 = "AH1_1";
            static constexpr auto AH1_2 = "AH1_2";

            static constexpr auto UB = "UB";
            static constexpr auto UB1 = "UB1";
            static constexpr auto UB1_1 = "UB1_1";
            static constexpr auto UB1_2 = "UB1_2";

            static constexpr auto W = "W";
            static constexpr auto W1 = "W1";
            static constexpr auto W2 = "W2";

            static constexpr auto T = "T";

            static constexpr auto H = "H";
            static constexpr auto H1 = "H1";

            static constexpr auto B = "B";
            static constexpr auto D = "D";
            static constexpr auto D1 = "D1";
            static constexpr auto D1_1 = "D1_1";
            static constexpr auto D2 = "D2";
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
        explicit Project1Composer(Project* project);

        static Project* createProject();

        PatternSpace* getBack() const;
        PatternSpace* getFront() const;

        void fillPatterns() override;
        void fillParameters() override;
        void fillInstructions() override;

        inline static const std::unordered_map<std::string, std::pair<double, double>> expectedBack = {
            {PointName::S, {0.0, 0.0}},
            {PointName::W, {0.0, -42.0}},
            {PointName::H, {0.0, -63.5}},
            {PointName::H1, {23.5, -63.5}},
            {PointName::W1, {23.5, -42.0}},
            {PointName::W2, {23.0, -42.0}},
            {PointName::S1, {23.0, 0.0}},
            {PointName::AH, {0.0, -21.0}},
            {PointName::UB, {0.0, -14.0}},
            {PointName::T, {0.0, -52.75}},
            {PointName::N, {6.3333, 0.0}},
            {PointName::N1, {6.3333, -2.375}},
            {PointName::N2, {0.0, -2.375}},
            {PointName::N3, {3.1666, -2.375}},
            {PointName::S2, {16.2344, -4.5419}},
            {PointName::AH1, {15.5, -21.0}},
            {PointName::UB1, {15.5, -14.0}},
            {PointName::AH2, {16.5606, -19.9393}},
            {PointName::AH3, {23.0, -21.0}},
            {PointName::AH4, {22.0, -21.0}},
            {PointName::D, {11.5641, -1.6995}},
            {PointName::DA, {9.401, -8.357}},
            {PointName::D1, {10.613, -1.3906}},
            {PointName::D2, {12.5152, -2.0086}},
        };
        inline static const std::unordered_map<std::string, std::pair<double, double>> expectedFront = {
            {PointName::S, {0.0, 0.0}},
            {PointName::W, {0.0, -42.0}},
            {PointName::H, {0.0, -63.5}},
            {PointName::AH, {0.0, -21.0}},
            {PointName::AH1, {-18.975, -21.0}},
            {PointName::AH1_1, {-9.336, -21.0}},
            {PointName::AH1_2, {-12.811, -21.0}},
            {PointName::UB, {0.0, -14.0}},
            {PointName::UB1, {-22.4499, -14.0}},
            {PointName::UB1_1, {-10.1722, -14.0}},
            {PointName::UB1_2, {-17.1221, -14.0}},
            {PointName::T, {0.0, -52.75}},
            {PointName::H1, {-25.5, -63.5}},
            {PointName::W1, {-25.5, -42.0}},
            {PointName::W2, {-25.0, -42.0}},
            {PointName::S1, {-25.0, 0.0}},
            {PointName::N, {-6.3333, 0.0}},
            {PointName::N1, {-6.3333, -5.345}},
            {PointName::N2, {0.0, -5.3449}},
            {PointName::N3, {-6.3333, -1.7817}},
            {PointName::N4, {-2.1111, -5.345}},
            {PointName::S2, {-27.0242, -8.3569}},
            {PointName::UB1, {-22.4499, -14.0}},
            {PointName::AH1, {-15.5, -21.0}},
            {PointName::AH2, {-17.2678, -19.2322}},
            {PointName::AH3, {-28.475, -21.0}},
            {PointName::AH4, {-27.475, -21.0}},
            {PointName::B, {0.0, -28.0}},
            {PointName::DA, {-8.5, -28.0}},
            {PointName::D1, {-11.7013, -1.198}},
            {PointName::D1_1, {-22.6548, -5.0165}},
        };
    };
}

#endif //CHRYSALIS_PROJECT1_H