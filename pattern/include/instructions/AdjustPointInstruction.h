#ifndef CHRYSALIS_ADJUSTPOINTINSTRUCTION_H
#define CHRYSALIS_ADJUSTPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"
#include "arguments/PointArgument.h"

namespace Chrysalis {
    class AdjustPointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(AdjustPointInstruction)
    public:
        /**
         * @uml{note[top] Syntax samples:
         * B -10-> A <-15- C
         */
        explicit AdjustPointInstruction(ProjectSpace* space, args::patterns* patterns, const args::name* pointName,
                                        const args::point* point1, const args::number* length1,
                                        const args::point* point2, const args::number* length2);
        ~AdjustPointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::name* pointName_;
        const args::point* point1_;
        const args::number* length1_;
        const args::point* point2_;
        const args::number* length2_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(AdjustPointInstruction, BasePatternInstruction, space_, patterns_, pointName_, point1_, length1_, point2_, length2_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::AdjustPointInstruction)

#endif //CHRYSALIS_ADJUSTPOINTINSTRUCTION_H