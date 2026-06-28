#ifndef CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H
#define CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    class UnfoldEdgeDartInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(UnfoldEdgeDartInstruction)
    public:
        explicit UnfoldEdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                           const args::name* edgePointFrom, const args::name* edgePointTo,
                                           const args::name* apexPoint, const args::name* leg1Point, const args::number* intake);
        ~UnfoldEdgeDartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::name* edgePointFrom_;
        const args::name* edgePointTo_;
        const args::name* apexPoint_;
        const args::name* leg1Point_;
        const args::number* intake_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(UnfoldEdgeDartInstruction, BasePatternInstruction, space_, patterns_, edgePointFrom_, edgePointTo_, apexPoint_, leg1Point_, intake_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::UnfoldEdgeDartInstruction)

#endif //CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H