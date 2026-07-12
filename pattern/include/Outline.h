#ifndef CHRYSALIS_OUTLINE_H
#define CHRYSALIS_OUTLINE_H

#include <vector>

#include "Point.h"
#include "NamedElementsContainer.h"

namespace Chrysalis {
    class Outline: public BaseNamedElement {
        SERIALIZE_DERIVED_FROM(BaseNamedElement)
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Outline)
    public:
        explicit Outline(const std::string& name);

        void add(const Point* point);
        [[nodiscard]] const std::vector<const Point*>& points() const;
    private:
        std::vector<const Point*> points_;
    };
    using OutlineContainer = NamedElementsContainer<Outline>;
}

#endif //CHRYSALIS_OUTLINE_H