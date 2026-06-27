#ifndef CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H
#define CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"

namespace Chrysalis {
    class SERIALIZABLE(IntersectionPointInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(IntersectionPointInstruction)
    public:
        explicit IntersectionPointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns, const args::name* pointName,
                                              const args::name* pointFrom1, const args::name* pointTo1,
                                              const args::name* pointFrom2, const args::name* pointTo2);
        ~IntersectionPointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::name* pointName_;
        const args::name* pointFrom1_;
        const args::name* pointTo1_;
        const args::name* pointFrom2_;
        const args::name* pointTo2_;
    };
    SERIALIZE_DERIVED_MEMBERS(IntersectionPointInstruction, BasePatternInstruction, pointName_, pointFrom1_, pointTo1_, pointFrom2_, pointTo2_)
    SERIALIZATION_CONSTRUCTOR(IntersectionPointInstruction, space_, selectedPatterns_, pointName_, pointFrom1_, pointTo1_, pointFrom2_, pointTo2_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::IntersectionPointInstruction)

#endif //CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H