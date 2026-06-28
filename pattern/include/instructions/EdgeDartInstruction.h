#ifndef CHRYSALIS_DARTINSTRUCTION_H
#define CHRYSALIS_DARTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"
#include "EdgeDartInstruction.h"
#include "arguments/OptionalArgument.h"
#include "arguments/PatternsContainerArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(EdgeDartInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(EdgeDartInstruction)
    public:
        explicit EdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                     const args::name* edgePointFrom, const args::name* edgePointTo, const args::vector* dartVector,
                                     const args::number* leg1Intake, const args::optional<args::number>* leg2Intake);
        ~EdgeDartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::name* edgePointFrom_;
        const args::name* edgePointTo_;
        const args::vector* dartVector_;
        const args::number* leg1Intake_;
        const args::optional<args::number>* leg2Intake_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(EdgeDartInstruction, BasePatternInstruction, space_, patterns_, edgePointFrom_, edgePointTo_, dartVector_, leg1Intake_, leg2Intake_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::EdgeDartInstruction)

#endif //CHRYSALIS_DARTINSTRUCTION_H