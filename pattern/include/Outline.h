#ifndef CHRYSALIS_OUTLINE_H
#define CHRYSALIS_OUTLINE_H

#include <list>
#include <string>

#include "serialization.h"

namespace Chrysalis {
    class SERIALIZABLE(Outline) {
        PROVIDE_SERIALIZATION_ACCESS(Outline)
        explicit Outline(const std::string& name);
    public:
        explicit Outline(const std::string& name, const std::string& firstPoint);

        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] const std::list<std::string>& getPoints() const;

        void addPoint(const std::string& name);

        static constexpr auto DEFAULT = "main";
    private:
        std::string name_;
        std::list<std::string> points_;
    };
    SERIALIZATION_CONSTRUCTOR(Outline, name_);
    SERIALIZE_MEMBERS(Outline, name_, points_);
}

#endif //CHRYSALIS_OUTLINE_H