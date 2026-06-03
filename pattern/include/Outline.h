#ifndef CHRYSALIS_OUTLINE_H
#define CHRYSALIS_OUTLINE_H

#include <list>
#include <string>

namespace Chrysalis {
    class Outline {
    public:
        explicit Outline(const std::string& name, const std::string& firstPoint);

        const std::string& getName();
        void addPoint(const std::string& name);

        static constexpr auto DEFAULT = "main";
    private:
        std::string name_;
        std::list<std::string> points_;
    };
}

#endif //CHRYSALIS_OUTLINE_H