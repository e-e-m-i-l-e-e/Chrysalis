#ifndef CHRYSALIS_OPTION_H
#define CHRYSALIS_OPTION_H

#include "BaseNamedElement.h"
#include "arguments/Argument.h"
#include "ScopedNamedElementsContainer.h"

namespace Chrysalis {
    struct OptionValue {
        explicit operator bool() const;
        bool value;
    };
    class Option: public BaseNamedElement, public Argument<OptionValue> {
        explicit Option(): Argument({false}) {};
        friend boost::serialization::access;
        template <class Archive>
        void serialize(Archive& archive, const unsigned int) {
            archive & boost::serialization::base_object<BaseNamedElement>(*this);
            archive & boost::serialization::base_object<Argument>(*this);
        }
    public:
        explicit Option(const std::string& name);
        static Option* createDefault(const std::string& name, bool isEnabled);

        void toggle();
    };
    using OptionsContainer = ScopedNamedElementsContainer<Option>;
}

#endif //CHRYSALIS_OPTION_H