#ifndef CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H
#define CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/SegmentArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    class UnfoldEdgeDartInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(UnfoldEdgeDartInstruction)
    public:
        explicit UnfoldEdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                           const args::segment* edge, const args::segment* leg, const args::number* intake);
        ~UnfoldEdgeDartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::segment* edge_;
        const args::segment* leg_;
        const args::number* intake_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(UnfoldEdgeDartInstruction, BasePatternInstruction, space_, patterns_, edge_, leg_, intake_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::UnfoldEdgeDartInstruction)

#endif //CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H