#include "Project.h"

#include <boost/serialization/export.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "Option.h"
#include "Expression.h"

#include "arguments/ParameterArgument.h"
#include "arguments/ComparisonArgument.h"
#include "arguments/BaseCalculatedArgument.h"
#include "arguments/BinaryFunctionArgument.h"
#include "arguments/ConditionalArgument.h"
#include "arguments/ExpressionArgument.h"
#include "arguments/VectorFunctionArgument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/OriginPointArgument.h"

#include "instructions/CurveInstruction.h"
#include "instructions/EdgeDartInstruction.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/MovePointInstruction.h"
#include "instructions/ExpressionInstruction.h"
#include "instructions/BuildOutlineInstruction.h"
#include "instructions/RelativePointInstruction.h"
#include "instructions/UnfoldEdgeDartInstruction.h"
#include "instructions/IntersectionPointInstruction.h"
#include "instructions/PatternInstructionsContainer.h"
#include "instructions/ConditionalInstructionsContainer.h"

using namespace Chrysalis;

BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::ParameterArgument)

BOOST_CLASS_EXPORT(Chrysalis::BinaryFunctionArgument::Add)
BOOST_CLASS_EXPORT(Chrysalis::BinaryFunctionArgument::Subtract)
BOOST_CLASS_EXPORT(Chrysalis::BinaryFunctionArgument::Multiply)
BOOST_CLASS_EXPORT(Chrysalis::BinaryFunctionArgument::Divide)
BOOST_CLASS_EXPORT(Chrysalis::BinaryFunctionArgument::Min)
BOOST_CLASS_EXPORT(Chrysalis::BinaryFunctionArgument::Max)

BOOST_CLASS_EXPORT(Chrysalis::VectorFunctionArgument::Length)
BOOST_CLASS_EXPORT(Chrysalis::VectorFunctionArgument::Angle)
BOOST_CLASS_EXPORT(Chrysalis::VectorFunctionArgument)

BOOST_CLASS_EXPORT(Chrysalis::ComparisonArgument::Equal)
BOOST_CLASS_EXPORT(Chrysalis::ComparisonArgument::NotEqual)
BOOST_CLASS_EXPORT(Chrysalis::ComparisonArgument::Greater)
BOOST_CLASS_EXPORT(Chrysalis::ComparisonArgument::GreaterEqual)
BOOST_CLASS_EXPORT(Chrysalis::ComparisonArgument::Less)
BOOST_CLASS_EXPORT(Chrysalis::ComparisonArgument::LessEqual)
BOOST_CLASS_EXPORT(Chrysalis::ComparisonArgument)

BOOST_CLASS_EXPORT(Chrysalis::Option)
BOOST_CLASS_EXPORT(Chrysalis::Expression)
BOOST_CLASS_EXPORT(Chrysalis::OptionsContainer)
BOOST_CLASS_EXPORT(Chrysalis::ExpressionsContainer)
BOOST_CLASS_EXPORT(Chrysalis::Argument<double>)
// BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::OptionalArgument<PointArgument>)
BOOST_CLASS_EXPORT(Chrysalis::ExpressionArgument)
BOOST_CLASS_EXPORT(Chrysalis::OriginPointArgument)
BOOST_CLASS_EXPORT(Chrysalis::PatternPointArgument)
BOOST_CLASS_EXPORT(Chrysalis::ConditionalArgument)

BOOST_CLASS_EXPORT(Chrysalis::CurveInstruction)
BOOST_CLASS_EXPORT(Chrysalis::ExpressionInstruction)
BOOST_CLASS_EXPORT(Chrysalis::PatternInstructionsContainer)
BOOST_CLASS_EXPORT(Chrysalis::BaseInstructionsContainer<BaseInstruction>)
BOOST_CLASS_EXPORT(Chrysalis::ConditionalInstructionsContainer)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::EdgeDartInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::FreePointInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::MovePointInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::BuildOutlineInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::RelativePointInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::UnfoldEdgeDartInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::IntersectionPointInstruction)

Project::Project(std::string name, ProjectSpace* space, PatternsContainer* patterns,
                 ParametersContainer* parameters, OptionsContainer* options,
                 ExpressionsContainer* expressions, InstructionsContainer* instructions)
    : name_(std::move(name)), space_(space), options_(options), patterns_(patterns), parameters_(parameters),
      expressions_(expressions),
      instructions_(instructions) {}

Project::~Project() {
    delete space_;
    delete patterns_;
    delete parameters_;
    delete expressions_;
    delete instructions_;
}

Project* Project::create() {
    return create("Untitled");
}

Project* Project::create(const std::string& name) {
    const auto globalOptions = new OptionsContainer();
    const auto globalExpressions = new ExpressionsContainer();
    return new Project(name, new ProjectSpace(), new PatternsContainer(), new ParametersContainer(),
                       globalOptions, globalExpressions,
                       new InstructionsContainer(
                           new OptionsContainer(globalOptions),
                           new ExpressionsContainer(globalExpressions)
                       )
    );
}

Project* Project::read(const std::string& filePath) {
    try {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filePath;
            return nullptr;
        }

        boost::archive::binary_iarchive archive(file);
        Project* project;
        archive >> project;
        return project;
    } catch (const boost::archive::archive_exception &e) {
        std::cout << "Archive error: " << e.what();
    } catch (const std::exception &e) {
        std::cout << "Read error: " << e.what();
    }
    return nullptr;
}

void Project::write(const std::string& filePath, Project* project) {
    try {
        std::ofstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filePath;
            return;
        }

        boost::archive::binary_oarchive archive(file);
        archive << project;

        file.flush();
        file.close();
    } catch (const boost::archive::archive_exception &e) {
        std::cout << "Archive error: " << e.what();
    } catch (const std::exception &e) {
        std::cout << "Write error: " << e.what();
    }
}

std::string Project::getName() {
    return name_;
}

void Project::setName(const std::string& name) {
    name_ = name;
}

ProjectSpace* Project::getSpace() const {
    return space_;
}

OptionsContainer* Project::getOptions() const {
    return options_;
}

PatternsContainer* Project::getPatterns() const {
    return patterns_;
}

ParametersContainer* Project::getParameters() const {
    return parameters_;
}

ExpressionsContainer* Project::getExpressions() const {
    return expressions_;
}

InstructionsContainer* Project::getInstructions() const {
    return instructions_;
}
