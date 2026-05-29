#ifndef CHRYSALIS_PROJECT_H
#define CHRYSALIS_PROJECT_H

#include <forward_list>

#include "serialization.h"

#include "Pattern.h"
#include "Parameters.h"

namespace Chrysalis {
    class SERIALIZABLE(Project) {
        PROVIDE_SERIALIZATION_ACCESS(Project)
    public:
        explicit Project(std::string  name, Parameters* parameters);
        ~Project();

        static Project* create();
        static Project* read(const std::string& filePath);
        static void write(const std::string& filePath, Project* project);

        std::string getName();
        void setName(const std::string& name);

        [[nodiscard]] Parameters* getParameters() const;

        void addPattern(Pattern* pattern);
    private:
        std::string name_;
        Parameters* parameters_;
        std::forward_list<Pattern*> patterns_;
    };

    SERIALIZE_MEMBERS(Project, name_, parameters_)
    SERIALIZATION_CONSTRUCTOR(Project, name_, parameters_)
}

#endif //CHRYSALIS_PROJECT_H