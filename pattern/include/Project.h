#ifndef CHRYSALIS_PROJECT_H
#define CHRYSALIS_PROJECT_H

#include "serialization.h"

#include "ProjectSpace.h"
#include "PatternsContainer.h"
#include "ParametersContainer.h"
#include "instructions/InstructionsContainer.h"

namespace Chrysalis {
    class Project {
        PROVIDE_SERIALIZATION_ACCESS(Project)
    public:
        static constexpr auto PROJECT_FILE_SUFFIX = "chrysalis";
        static constexpr auto PROJECT_NAME_FILTER = "Chrysalis Project (*.chrysalis)";

        explicit Project(std::string name, ProjectSpace* space, ParametersContainer* parameters,
                         PatternsContainer* patterns, InstructionsContainer* instructions);
        ~Project();

        static Project* create();
        static Project* create(const std::string& name);

        static Project* read(const std::string& filePath);
        static void write(const std::string& filePath, Project* project);

        std::string getName();
        void setName(const std::string& name);

        [[nodiscard]] ProjectSpace* getSpace() const;
        [[nodiscard]] PatternsContainer* getPatterns() const;
        [[nodiscard]] ParametersContainer* getParameters() const;
        [[nodiscard]] InstructionsContainer* getInstructions() const;
    private:
        std::string name_;
        /// @uml{composition[]}
        ProjectSpace* space_;
        /// @uml{composition[]}
        PatternsContainer* patterns_;
        /// @uml{composition[]}
        ParametersContainer* parameters_;
        /// @uml{composition[]}
        InstructionsContainer* instructions_;
    };
    SERIALIZE_CONSTRUCTION(Project, name_, space_, parameters_, patterns_, instructions_)
}

#endif //CHRYSALIS_PROJECT_H