#ifndef CHRYSALIS_BASENAMEDINPUT_H
#define CHRYSALIS_BASENAMEDINPUT_H

#include "serialization.h"

#include <string>
#include <boost/optional/optional.hpp>

namespace Chrysalis {
    class BaseNamedElement {
    protected:
        SERIALIZE(name_, alias_)
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(BaseNamedElement)
        explicit BaseNamedElement(const std::string& name);
    public:
        [[nodiscard]] bool hasAlias() const;

        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] const std::string& getAlias() const;

        void setName(const std::string& name);
        void setAlias(const std::string& alias);
    private:
        std::string name_;
        boost::optional<std::string> alias_;
    };
}

#endif //CHRYSALIS_BASENAMEDINPUT_H