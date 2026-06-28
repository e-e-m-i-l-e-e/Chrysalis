#ifndef CHRYSALIS_PATTERNSCONTAINER_H
#define CHRYSALIS_PATTERNSCONTAINER_H

#include "Pattern.h"
#include "BaseContainer.h"
#include "PatternsContainer.h"

#include "serialization.h"

namespace Chrysalis {
    class PatternsContainer: public BaseContainer<Pattern> {
        SERIALIZE_DERIVED_FROM(BaseContainer, patterns_)
    public:
        void add(Pattern* item) override;
        [[nodiscard]] Pattern* get(const std::string& name) const;
    private:
        std::unordered_map<std::string, Pattern*> patterns_;
    };
}

#endif //CHRYSALIS_PATTERNSCONTAINER_H