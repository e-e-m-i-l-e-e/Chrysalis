#ifndef CHRYSALIS_ADDPOINTINSTRUCTION_H
#define CHRYSALIS_ADDPOINTINSTRUCTION_H

#include <string>
#include <boost/optional/optional.hpp>

#include "PatternSpacesArgument.h"
#include "Argument.h"
#include "PatternSpace.h"
#include "BaseInstruction.h"
#include "BasePatternSpacesInstruction.h"

namespace Chrysalis {
    /**
     * \uml{note[top] Syntax samples:
     *
     * }
     */
    class RelativePointInstruction: public BasePatternSpacesInstruction {
    public:
        explicit RelativePointInstruction(ProjectSpace* space,
                                          Argument<PatternSpacesArgument*>* patternSpaces,
                                          Argument<std::string>* pointFrom,
                                          Argument<PatternSpace*>* pointFromPatternSpace,
                                          Argument<std::string>* pointTo,
                                          Argument<double>* angle,
                                          Argument<double>* distance);
        ~RelativePointInstruction() override;

        void reset() override;
        bool isValid() override;
        void execute() override;
    private:
        Argument<std::string>* pointFrom_;
        Argument<PatternSpace*>* pointFromPatternSpace_;
        Argument<std::string>* pointTo_;
        Argument<double>* angle_;
        Argument<double>* distance_;
    };
}

#endif //CHRYSALIS_ADDPOINTINSTRUCTION_H