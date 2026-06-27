#ifndef CHRYSALIS_DARTINSTRUCTION_H
#define CHRYSALIS_DARTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"
#include "EdgeDartInstruction.h"

namespace Chrysalis {
    class SERIALIZABLE(EdgeDartInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(EdgeDartInstruction)
    public:
        explicit EdgeDartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                     const name* edgePointFrom, const name* edgePointTo, const vector* dartVector,
                                     const num* leg1Intake, const num* leg2Intake);
        ~EdgeDartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* edgePointFrom_;
        const name* edgePointTo_;
        const vector* dartVector_;
        const num* leg1Intake_;
        const num* leg2Intake_;
    };
    SERIALIZE_DERIVED_MEMBERS(Chrysalis::EdgeDartInstruction, Chrysalis::BasePatternInstruction, edgePointFrom_, edgePointTo_, dartVector_, leg1Intake_, leg2Intake_)
    SERIALIZATION_CONSTRUCTOR(Chrysalis::EdgeDartInstruction, space_, selectedPatterns_, edgePointFrom_, edgePointTo_, dartVector_, leg1Intake_, leg2Intake_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::EdgeDartInstruction)

#endif //CHRYSALIS_DARTINSTRUCTION_H