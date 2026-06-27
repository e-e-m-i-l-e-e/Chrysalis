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
                                        const point* point1, const num* length1,
                                        const point* point2, const num* length2);
        ~AdjustPointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* pointName_;
        const point* point1_;
        const num* length1_;
        const point* point2_;
        const num* length2_;
    };
    SERIALIZE_DERIVED_MEMBERS(Chrysalis::AdjustPointInstruction, Chrysalis::BasePatternInstruction, pointName_, point1_, length1_, point2_, length2_)
    SERIALIZATION_CONSTRUCTOR(Chrysalis::AdjustPointInstruction, space_, selectedPatterns_, pointName_, point1_, length1_, point2_, length2_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::AdjustPointInstruction)

#endif //CHRYSALIS_ADJUSTPOINTINSTRUCTION_H