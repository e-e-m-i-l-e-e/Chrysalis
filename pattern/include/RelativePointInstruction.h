#ifndef CHRYSALIS_ADDPOINTINSTRUCTION_H
#define CHRYSALIS_ADDPOINTINSTRUCTION_H

#include <string>
#include <boost/optional/optional.hpp>

#include "PatternSpacesArgument.h"
#include "Argument.h"
#include "PatternSpace.h"
#include "BasePatternInstruction.h"
#include "NameArgument.h"
#include "NumberArgument.h"
#include "PatternArgument.h"

namespace Chrysalis {
    using name = NameArgument;
    using num = NumberArgument;
    using pattern = PatternArgument;
    /**
     * \uml{note[top] Syntax samples:
     *
     * }
     */
    class RelativePointInstruction: public BasePatternInstruction {
    public:
        explicit RelativePointInstruction(ProjectSpace* space,
                                          Argument<PatternSpacesArgument*>* patternSpaces,
                                          name* pointFrom,
                                          pattern* pointFromPattern,
                                          name* pointTo,
                                          num* angle,
                                          num* distance);
        ~RelativePointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        name* pointFrom_;
        pattern* pointFromPattern_;
        name* pointTo_;
        num* angle_;
        num* distance_;
    };
}

#endif //CHRYSALIS_ADDPOINTINSTRUCTION_H