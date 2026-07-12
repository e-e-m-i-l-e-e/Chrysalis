#ifndef CHRYSALIS_INSTRUCTIONS_H
#define CHRYSALIS_INSTRUCTIONS_H

#include "Project.h"
#include "instructions/BaseInstructionsContainer.h"

namespace Chrysalis::Composer {
    class Instructions {
    public:
        explicit Instructions(const Project* project);
        ~Instructions();

        void operator<<(const std::initializer_list<BaseInstruction*>& instructions) const;

        static inline ProjectSpace* space = nullptr;
        static inline InstructionsContainer* instructionsContainer = nullptr;
    private:
        InstructionsContainer* outerInstructionsContainer_;
    };
}

#endif //CHRYSALIS_INSTRUCTIONS_H
