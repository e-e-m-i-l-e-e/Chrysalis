#ifndef CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H

#include "arguments/PatternsContainerArgument.h"
#include "instructions/BasePatternInstruction.h"
#include "instructions/BaseInstructionsContainer.h"

/** @defgroup Instructions Instructions
 *  @{
 */
namespace Chrysalis {
    class PatternInstructionsContainer: public BaseInstructionsContainer<BasePatternInstruction> {
        PROVIDE_SERIALIZATION_ACCESS(PatternInstructionsContainer)
    public:
        explicit PatternInstructionsContainer(OptionsContainer* options, ExpressionsContainer* expressions, args::patterns* patterns);
        ~PatternInstructionsContainer() override;
    private:
        /// @uml{composition}
        args::patterns* patterns_;
    };
    template <class Archive>
    void serialize(Archive& archive, PatternInstructionsContainer& obj, const unsigned int version)
    {
        archive & boost::serialization::base_object<BaseInstructionsContainer<BasePatternInstruction>>(obj);
    }

    template <class Archive>
    void save_construct_data(Archive& archive, const PatternInstructionsContainer* obj, const unsigned int)
    {
        archive & obj->options();
        archive & obj->expressions();
        archive & obj->patterns_;
    }

    template <class Archive>
    void load_construct_data(Archive& archive, PatternInstructionsContainer* obj, const unsigned int)
    {
        decltype(obj->options()) options_;
        decltype(obj->expressions()) expressions_;
        decltype(obj->patterns_) patterns_;
        archive >> options_;
        archive >> expressions_;
        archive >> patterns_;
        ::new(obj) PatternInstructionsContainer(options_, expressions_, patterns_);
    }
}
/**@}*/

#endif //CHRYSALIS_PATTERNINSTRUCTIONSCONTAINER_H