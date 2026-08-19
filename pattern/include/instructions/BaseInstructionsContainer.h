#ifndef CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H

#include "Option.h"
#include "Expression.h"
#include "BaseInstruction.h"
#include "CompositiveContainer.h"

/** @defgroup Instructions Instructions
 *  @{
 */
namespace Chrysalis {
    template<typename T>
    requires std::derived_from<T, BaseInstruction>
    class BaseInstructionsContainer: public BaseInstruction, public CompositiveContainer<T> {
        PROVIDE_SERIALIZATION_ACCESS_T(BaseInstructionsContainer)
    public:
        explicit BaseInstructionsContainer(OptionsContainer* options, ExpressionsContainer* expressions)
            : options_(options), expressions_(expressions) {}
        ~BaseInstructionsContainer() override {
            delete options_;
            delete expressions_;
        }
        void execute() override {
            for (const auto& instruction: *this) {
                instruction->execute();
            }
        }
        [[nodiscard]] OptionsContainer* options() const {
            return options_;
        }
        [[nodiscard]] ExpressionsContainer* expressions() const {
            return expressions_;
        }
    private:
        /// @uml{composition}
        OptionsContainer* options_;
        /// @uml{composition}
        ExpressionsContainer* expressions_;
    };
    SERIALIZE_BASE_T(BaseInstructionsContainer, BaseInstruction, CompositiveContainer<T>)
    template <class Archive, typename T>
    void serialize(Archive& archive, BaseInstructionsContainer<T>& obj, const unsigned int version) {
        serialize_base(archive, obj);
    }

    template <class Archive, typename T>
    void save_construct_data(Archive& archive, const BaseInstructionsContainer<T>* obj, const unsigned int)
    {
        archive & obj->options_;
        archive & obj->expressions_;
    }

    template <class Archive, typename T>
    void load_construct_data(Archive& archive, BaseInstructionsContainer<T>* obj, const unsigned int)
    {
        decltype(obj->options_) options_;
        decltype(obj->expressions_) expressions_;
        archive >> options_;
        archive >> expressions_;
        ::new(obj) BaseInstructionsContainer<T>(options_, expressions_);
    }
    using InstructionsContainer = BaseInstructionsContainer<BaseInstruction>;
}
/**@}*/

#endif //CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H