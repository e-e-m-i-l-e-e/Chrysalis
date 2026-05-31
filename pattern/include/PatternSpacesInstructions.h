#ifndef CHRYSALIS_PATTERNSPACESINSTRUCTIONS_H
#define CHRYSALIS_PATTERNSPACESINSTRUCTIONS_H

#include "BaseInstruction.h"
#include "BasePatternSpacesInstruction.h"

namespace Chrysalis {
    class PatternSpacesInstructions: public BaseInstruction {
    public:
        void addInstruction(BasePatternSpacesInstruction* instruction);
        void reset() override;
        bool isValid() override;
        void execute() override;
    private:
        std::list<BasePatternSpacesInstruction*> instructions_;
    };
}

#endif //CHRYSALIS_PATTERNSPACESINSTRUCTIONS_H