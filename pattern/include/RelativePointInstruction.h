#ifndef CHRYSALIS_ADDPOINTINSTRUCTION_H
#define CHRYSALIS_ADDPOINTINSTRUCTION_H

#include <string>
#include <boost/optional/optional.hpp>

#include "Argument.h"
#include "PatternSpace.h"
#include "BaseInstruction.h"
#include "PatternSpacesArgument.h"

/**
 * \uml{note[top] Syntax samples:
 *
 * }
 */
class RelativePointInstruction: public BaseInstruction {
public:
    explicit RelativePointInstruction(Space* space,
                                 PatternSpacesArgument* patternSpaces,
                                 Argument<std::string>* pointFrom,
                                 Argument<std::string>* pointTo,
                                 Argument<double>* angle,
                                 Argument<double>* distance);
    ~RelativePointInstruction() override;

    void reset() override;
    void execute() override;
private:
    Space* space_;
    PatternSpacesArgument* patternSpaces_;

    Argument<std::string>* pointFrom_;
    Argument<std::string>* pointTo_;
    Argument<double>* angle_;
    Argument<double>* distance_;
};

#endif //CHRYSALIS_ADDPOINTINSTRUCTION_H