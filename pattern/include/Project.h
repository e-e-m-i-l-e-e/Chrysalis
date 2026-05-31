#ifndef CHRYSALIS_PROJECT_H
#define CHRYSALIS_PROJECT_H

#include <forward_list>

#include "serialization.h"

#include "Pattern.h"
#include "Parameters.h"
#include "Instructions.h"
#include "ProjectSpace.h"

namespace Chrysalis {
    class SERIALIZABLE(Project) {
        PROVIDE_SERIALIZATION_ACCESS(Project)
    public:
        explicit Project(std::string name, ProjectSpace* space, Parameters* parameters, Instructions* instructions);
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
        /// @uml{composition[]}
        ProjectSpace* space_;
        /// @uml{composition[]}
        Parameters* parameters_;
        /// @uml{composition[]}
        Instructions* instructions_;
        std::forward_list<Pattern*> patterns_;
    };

    SIMPLE_SERIALIZE_MEMBERS(Project, name_, space_, parameters_, instructions_)
}

#endif //CHRYSALIS_PROJECT_H