#ifndef CHRYSALIS_PATTERNINSTRUCTIONS_H
#define CHRYSALIS_PATTERNINSTRUCTIONS_H

#include "instructions/PatternInstructionsContainer.h"

namespace Chrysalis::Composer {
    class PatternInstructions {
    public:
        explicit PatternInstructions(args::patterns* selectedPatterns);
        ~PatternInstructions();

        BaseInstruction* operator<<(const std::initializer_list<std::vector<BasePatternInstruction*>>& patternInstructions) const;

        static inline args::patterns* patterns = nullptr;
        static inline PatternInstructionsContainer* instructions = nullptr;
    };
}

#endif //CHRYSALIS_PATTERNINSTRUCTIONS_H
