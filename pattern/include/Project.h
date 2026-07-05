#ifndef CHRYSALIS_PROJECT_H
#define CHRYSALIS_PROJECT_H

#include "serialization.h"

#include "Pattern.h"
#include "Parameter.h"
#include "Expression.h"
#include "ProjectSpace.h"
#include "instructions/PatternInstructionsContainer.h"

namespace Chrysalis {
    class Project {
        PROVIDE_SERIALIZATION_ACCESS(Project)
    public:
        static constexpr auto PROJECT_FILE_SUFFIX = "chrysalis";
        static constexpr auto PROJECT_NAME_FILTER = "Chrysalis Project (*.chrysalis)";

        explicit Project(std::string name, ProjectSpace* space, ParametersContainer* parameters,
                         ExpressionsContainer* expressions, PatternsContainer* patterns,
                         InstructionsContainer* instructions);
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
        [[nodiscard]] ExpressionsContainer* getExpressions() const;
        [[nodiscard]] InstructionsContainer* getInstructions() const;
    private:
        std::string name_;
        /// @uml{composition}
        ProjectSpace* space_;
        /// @uml{composition}
        PatternsContainer* patterns_;
        /// @uml{composition}
        ParametersContainer* parameters_;
        /// @uml{composition}
        ExpressionsContainer* expressions_;
        /// @uml{composition}
        InstructionsContainer* instructions_;
    };
    SERIALIZE_CONSTRUCTION(Project, name_, space_, parameters_, expressions_, patterns_, instructions_)
}

#endif //CHRYSALIS_PROJECT_H