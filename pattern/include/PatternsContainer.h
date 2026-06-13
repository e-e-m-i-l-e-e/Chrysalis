#ifndef CHRYSALIS_PATTERNSCONTAINER_H
#define CHRYSALIS_PATTERNSCONTAINER_H

#include "Pattern.h"
#include "BaseContainer.h"
#include "PatternsContainer.h"

#include "serialization.h"

namespace Chrysalis {
    class SERIALIZABLE(PatternsContainer): public BaseContainer<Pattern> {
        PROVIDE_SERIALIZATION_ACCESS(PatternsContainer)
    public:
        void add(Pattern* item) override;
        [[nodiscard]] Pattern* get(const std::string& name) const;
    private:
        std::unordered_map<std::string, Pattern*> patterns_;
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(PatternsContainer, BaseContainer<Pattern>, patterns_)
}

#endif //CHRYSALIS_PATTERNSCONTAINER_H