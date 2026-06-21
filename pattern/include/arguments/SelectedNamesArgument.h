#ifndef CHRYSALIS_SELECTEDNAMES_H
#define CHRYSALIS_SELECTEDNAMES_H

#include <list>
#include <string>

namespace Chrysalis {
    class SelectedNamesArgument {
    public:
        void add(const std::string& name);

        std::list<std::string>::const_iterator begin() const;
        std::list<std::string>::const_iterator end() const;
    private:
        std::list<std::string> names_;
    };
}

#endif //CHRYSALIS_SELECTEDNAMES_H