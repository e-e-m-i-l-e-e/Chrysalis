#ifndef CHRYSALIS_BASENAMEDINPUT_H
#define CHRYSALIS_BASENAMEDINPUT_H

#include "serialization.h"

#include <string>
#include <boost/optional/optional.hpp>

namespace Chrysalis {
    class SERIALIZABLE(BaseNamedInput) {
    protected:
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(BaseNamedInput)
        explicit BaseNamedInput(const std::string& name);
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
    DEFAULT_SERIALIZE_MEMBERS(BaseNamedInput, name_, alias_);
}

#endif //CHRYSALIS_BASENAMEDINPUT_H