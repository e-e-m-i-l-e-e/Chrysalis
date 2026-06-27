#ifndef CHRYSALIS_BASEPATTERNINSTRUCTION_H
#define CHRYSALIS_BASEPATTERNINSTRUCTION_H

#include "ProjectSpace.h"
#include "BaseInstruction.h"

#include "arguments/BaseArgument.h"
#include "arguments/PointArgument.h"
#include "arguments/VectorArgument.h"
#include "arguments/SelectedPatternsArgument.h"

namespace Chrysalis {
    using point = PointArgument;
    using vector = VectorArgument;

    class SERIALIZABLE(BasePatternInstruction): public BaseInstruction {
        PROVIDE_SERIALIZATION_ACCESS(BasePatternInstruction)
    public:
        ~BasePatternInstruction() override;
        virtual bool isValid() = 0;
    protected:
        explicit BasePatternInstruction(ProjectSpace* space, SelectedPatternsArgument* selectedPatterns);

        [[nodiscard]] ProjectSpace& space() const {
            return *space_;
        }
        [[nodiscard]] SelectedPatterns& patterns() const {
            return *selectedPatterns_->get();
        }
        bool eachPatternHasPoint(const std::string& point) const;
        bool allPatternsSharePoint(const std::string& point) const;
        const PatternSpace* anyPattern() const;

        ProjectSpace* space_;
        /// @uml{composition}
        SelectedPatternsArgument* selectedPatterns_;
    };
    SERIALIZE_MEMBERS(BasePatternInstruction, space_, selectedPatterns_);
};

#endif //CHRYSALIS_BASEPATTERNINSTRUCTION_H