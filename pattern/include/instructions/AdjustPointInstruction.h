#ifndef CHRYSALIS_ADJUSTPOINTINSTRUCTION_H
#define CHRYSALIS_ADJUSTPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"

namespace Chrysalis {
    class SERIALIZABLE(AdjustPointInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(AdjustPointInstruction)
    public:
        /**
         * @uml{note[top] Syntax samples:
         * B -10-> A <-15- C
         */
        explicit AdjustPointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns, const name* pointName,
                                        const name* pointName1, const num* length1,
                                        const name* pointName2, const num* length2);
        ~AdjustPointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* pointName_;
        const name* pointName1_;
        const num* length1_;
        const name* pointName2_;
        const num* length2_;
    };
    SERIALIZE_DERIVED_MEMBERS(Chrysalis::AdjustPointInstruction, Chrysalis::BasePatternInstruction, pointName_, pointName1_, length1_, pointName2_, length2_)
    SERIALIZATION_CONSTRUCTOR(Chrysalis::AdjustPointInstruction, space_, selectedPatterns_, pointName_, pointName1_, length1_, pointName2_, length2_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::AdjustPointInstruction)

#endif //CHRYSALIS_ADJUSTPOINTINSTRUCTION_H