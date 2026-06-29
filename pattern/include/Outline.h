#ifndef CHRYSALIS_OUTLINE_H
#define CHRYSALIS_OUTLINE_H

#include <vector>

#include "NamedElementsContainer.h"

namespace Chrysalis {
    class Outline: public BaseNamedElement {
        SERIALIZE_DERIVED_FROM(BaseNamedElement)
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Outline)
    public:
        explicit Outline(const std::string& name);

        void add(const std::string& name);
        [[nodiscard]] const std::vector<std::string>& points() const;
    private:
        std::vector<std::string> points_;
    };
    using OutlineContainer = NamedElementsContainer<Outline>;
}

#endif //CHRYSALIS_OUTLINE_H