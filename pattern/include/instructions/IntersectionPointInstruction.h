#ifndef CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H
#define CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/LineArgument.h"
#include "arguments/BaseArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    class IntersectionPointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(IntersectionPointInstruction)
    public:
        explicit IntersectionPointInstruction(ProjectSpace* space, args::patterns* patterns,
                                              const args::line* line,
                                              const args::container<args::name>* names,
                                              const args::container<args::line>* targets);
        ~IntersectionPointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::line* line_;
        const args::container<args::name>* names_;
        const args::container<args::line>* targets_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(IntersectionPointInstruction, BasePatternInstruction, space_, patterns_, line_, names_, targets_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::IntersectionPointInstruction)

#endif //CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H