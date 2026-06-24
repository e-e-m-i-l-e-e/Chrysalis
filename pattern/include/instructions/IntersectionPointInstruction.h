#ifndef CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H
#define CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"

namespace Chrysalis {
    class SERIALIZABLE(IntersectionPointInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(IntersectionPointInstruction)
    public:
        explicit IntersectionPointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns, const name* pointName,
                                              const name* pointFrom1, const name* pointTo1,
                                              const name* pointFrom2, const name* pointTo2);
        ~IntersectionPointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* pointName_;
        const name* pointFrom1_;
        const name* pointTo1_;
        const name* pointFrom2_;
        const name* pointTo2_;
    };
    SERIALIZE_DERIVED_MEMBERS(IntersectionPointInstruction, BasePatternInstruction, pointName_, pointFrom1_, pointTo1_, pointFrom2_, pointTo2_)
    SERIALIZATION_CONSTRUCTOR(IntersectionPointInstruction, space_, selectedPatterns_, pointName_, pointFrom1_, pointTo1_, pointFrom2_, pointTo2_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::IntersectionPointInstruction)

#endif //CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H