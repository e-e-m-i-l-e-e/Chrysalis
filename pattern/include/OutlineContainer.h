#ifndef CHRYSALIS_OUTLINECONTAINER_H
#define CHRYSALIS_OUTLINECONTAINER_H

#include <string>
#include <unordered_map>

#include "Outline.h"
#include "BaseContainer.h"

namespace Chrysalis {
    class SERIALIZABLE(OutlineContainer): public BaseContainer<Outline> {
    public:
        void add(Outline* item) override;
        [[nodiscard]] bool has(const std::string& name) const;
        [[nodiscard]] Outline* get(const std::string& name) const;
    private:
        std::unordered_map<std::string, Outline*> outlines_;
    };
    DEFAULT_SERIALIZE_MEMBERS(OutlineContainer)
}

#endif //CHRYSALIS_OUTLINECONTAINER_H