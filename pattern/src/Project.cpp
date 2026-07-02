#include "Project.h"

#include <boost/serialization/export.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "arguments/BaseArgument.h"
#include "arguments/ParameterArgument.h"
#include "arguments/BaseCalculatedArgument.h"
#include "arguments/BinaryFunctionArgument.h"
#include "arguments/VectorFunction.h"
#include "arguments/VectorFunctionArgument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/OriginPointArgument.h"

#include "instructions/EdgeDartInstruction.h"
#include "instructions/FreePointInstruction.h"
#include "instructions/MovePointInstruction.h"
#include "instructions/AdjustPointInstruction.h"
#include "instructions/BuildOutlineInstruction.h"
#include "instructions/RelativePointInstruction.h"
#include "instructions/UnfoldEdgeDartInstruction.h"
#include "instructions/IntersectionPointInstruction.h"

using namespace Chrysalis;

BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::ParameterArgument)

BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::BinaryFunction::Add)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::BinaryFunction::Subtract)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::BinaryFunction::Multiply)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::BinaryFunction::Divide)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::BinaryFunctionArgument)

BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::VectorFunction::Length)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::VectorFunction::Angle)
BOOST_CLASS_EXPORT(Chrysalis::VectorFunctionArgument)

BOOST_CLASS_EXPORT(Chrysalis::Argument<double>)
// BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::OptionalArgument<PointArgument>)
BOOST_CLASS_EXPORT(Chrysalis::OriginPointArgument)
BOOST_CLASS_EXPORT(Chrysalis::PatternPointArgument)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::EdgeDartInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::FreePointInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::MovePointInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::AdjustPointInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::BuildOutlineInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::RelativePointInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::UnfoldEdgeDartInstruction)
BOOST_CLASS_EXPORT_IMPLEMENT(Chrysalis::IntersectionPointInstruction)

Project::Project(std::string name, ProjectSpace* space, ParametersContainer* parameters,
                 PatternsContainer* patterns, InstructionsContainer* instructions)
    : name_(std::move(name)), space_(space), patterns_(patterns), parameters_(parameters), instructions_(instructions) {}

Project::~Project() {
    delete space_;
    delete patterns_;
    delete parameters_;
    delete instructions_;
}

Project* Project::create() {
    return create("Untitled");
}

Project* Project::create(const std::string& name) {
    return new Project(name, new ProjectSpace(), new ParametersContainer(), new PatternsContainer(), new InstructionsContainer());
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

PatternsContainer* Project::getPatterns() const {
    return patterns_;
}

ParametersContainer* Project::getParameters() const {
    return parameters_;
}

InstructionsContainer* Project::getInstructions() const {
    return instructions_;
}
