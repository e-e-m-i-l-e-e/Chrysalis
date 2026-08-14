#ifndef CHRYSALIS_EDGEDARTINSTRUCTION_H
#define CHRYSALIS_EDGEDARTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/SegmentArgument.h"
#include "arguments/OptionalArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    /**
     * @defgroup Instructions
     * @{
     */
    class EdgeDartInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(EdgeDartInstruction)
    public:
        explicit EdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                     const args::segment* edge, const args::vector* dart,
                                     args::number&& leg1Intake, const args::optional<args::number>* leg2Intake);
        ~EdgeDartInstruction() override;

        void execute() override;
    private:
        /// @uml{composition}
        const args::segment* edge_;
        /// @uml{composition}
        const args::vector* dart_;
        /// @uml{composition}
        args::number leg1Intake_;
        /// @uml{composition}
        const args::optional<args::number>* leg2Intake_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(EdgeDartInstruction, BasePatternInstruction, space_, patterns_, edge_, dart_, leg1Intake_, leg2Intake_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::EdgeDartInstruction)

#endif //CHRYSALIS_EDGEDARTINSTRUCTION_H