#ifndef CHRYSALIS_ADDPOINTINSTRUCTION_H
#define CHRYSALIS_ADDPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"
#include "RelativePointInstruction.h"
#include "arguments/OptionalArgument.h"
#include "arguments/PointArgument.h"
#include "arguments/PatternsContainerArgument.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * A -> B 45 10
     * "A 1" ("Back") -> "B 2" 1 / 2 * 3 param("Short alias")
     * A -> B (1 * 2 * 3 * 4) (1 / 2 / param("Circumference of something"))
     * }
     */
    class RelativePointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(RelativePointInstruction)
    public:
        explicit RelativePointInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                          const args::optional<args::point>* origin, const args::name* pointTo, const args::number* angle, const args::number* distance);
        ~RelativePointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::optional<args::point>* origin_;
        const args::name* pointTo_;
        const args::number* angle_;
        const args::number* distance_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(RelativePointInstruction, BasePatternInstruction, space_, patterns_, origin_, pointTo_, angle_, distance_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::RelativePointInstruction)

#endif //CHRYSALIS_ADDPOINTINSTRUCTION_H