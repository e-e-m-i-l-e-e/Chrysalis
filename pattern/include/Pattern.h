#ifndef CHRYSALIS_PATTERN_H
#define CHRYSALIS_PATTERN_H

#include "PatternSpace.h"
#include "NamedElementsContainer.h"

namespace Chrysalis {
    class Pattern: public BaseNamedElement {
        SERIALIZE_DERIVED_FROM(BaseNamedElement, space_)
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Pattern)
    public:
        explicit Pattern(const std::string& name, PatternSpace* space);
        ~Pattern();

        static Pattern* create(const std::string& name);

        [[nodiscard]] PatternSpace* getSpace() const;
    private:
        /// @uml{composition[]}
        PatternSpace* space_;
    };
    using PatternsContainer = NamedElementsContainer<Pattern>;
}

#endif //CHRYSALIS_PATTERN_H