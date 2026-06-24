#ifndef CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H
#define CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    class SERIALIZABLE(UnfoldEdgeDartInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(UnfoldEdgeDartInstruction)
    public:
        explicit UnfoldEdgeDartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                           const name* edgePointFrom, const name* edgePointTo,
                                           const name* apexPoint, const name* leg1Point, const num* intake);
        ~UnfoldEdgeDartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* edgePointFrom_;
        const name* edgePointTo_;
        const name* apexPoint_;
        const name* leg1Point_;
        const num* intake_;
    };
    SERIALIZE_DERIVED_MEMBERS(UnfoldEdgeDartInstruction, BasePatternInstruction, edgePointFrom_, edgePointTo_, apexPoint_, leg1Point_, intake_)
    SERIALIZATION_CONSTRUCTOR(UnfoldEdgeDartInstruction, space_, selectedPatterns_, edgePointFrom_, edgePointTo_, apexPoint_, leg1Point_, intake_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::UnfoldEdgeDartInstruction)

#endif //CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H