#ifndef CHRYSALIS_OUTLINECONTAINER_H
#define CHRYSALIS_OUTLINECONTAINER_H

#include <string>
#include <unordered_map>

#include "Outline.h"
#include "BaseContainer.h"

namespace Chrysalis {
    class SERIALIZABLE(OutlineContainer): public BaseContainer<Outline> {
        PROVIDE_SERIALIZATION_ACCESS(OutlineContainer)
    public:
        void add(Outline* item) override;
        bool has(const std::string& name) const;
        Outline* get(const std::string& name) const;
    private:
        std::unordered_map<std::string, Outline*> outlines_;
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(OutlineContainer, BaseContainer<Outline>, outlines_)
}

#endif //CHRYSALIS_OUTLINECONTAINER_H