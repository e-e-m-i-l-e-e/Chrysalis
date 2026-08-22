#include "Project.h"

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/unique_ptr.hpp>

#include "exceptions/ProjectIOError.h"

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
#include "arguments/OptionArgument.h"
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
#include "instructions/DartInstruction.h"
#include "instructions/ResetTransformationInstruction.h"
#include "instructions/TransformInstruction.h"

using namespace Chrysalis;

BOOST_CLASS_EXPORT(Chrysalis::ParameterArgument)

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

BOOST_CLASS_EXPORT(Chrysalis::LineArgument)
BOOST_CLASS_EXPORT(Chrysalis::RayArgument)
BOOST_CLASS_EXPORT(Chrysalis::VectorArgument)
BOOST_CLASS_EXPORT(Chrysalis::SegmentArgument)

BOOST_CLASS_EXPORT(Chrysalis::Option)
BOOST_CLASS_EXPORT(Chrysalis::Expression)
BOOST_CLASS_EXPORT(Chrysalis::OptionsContainer)
BOOST_CLASS_EXPORT(Chrysalis::ExpressionsContainer)
BOOST_CLASS_EXPORT(Chrysalis::Argument<double>)
BOOST_CLASS_EXPORT(Chrysalis::OptionArgument)
BOOST_CLASS_EXPORT(Chrysalis::ExpressionArgument)
BOOST_CLASS_EXPORT(Chrysalis::OriginPointArgument)
BOOST_CLASS_EXPORT(Chrysalis::PatternPointArgument)
BOOST_CLASS_EXPORT(Chrysalis::ConditionalArgument)

BOOST_CLASS_EXPORT(Chrysalis::TransformInstruction)
BOOST_CLASS_EXPORT(Chrysalis::ResetTransformationInstruction)
BOOST_CLASS_EXPORT(Chrysalis::DartInstruction)
BOOST_CLASS_EXPORT(Chrysalis::CurveInstruction)
BOOST_CLASS_EXPORT(Chrysalis::ExpressionInstruction)
BOOST_CLASS_EXPORT(Chrysalis::PatternInstructionsContainer)
BOOST_CLASS_EXPORT(Chrysalis::BaseInstructionsContainer<BaseInstruction>)
BOOST_CLASS_EXPORT(Chrysalis::ConditionalInstructionsContainer)
BOOST_CLASS_EXPORT(Chrysalis::FreePointInstruction)
BOOST_CLASS_EXPORT(Chrysalis::EdgeDartInstruction)
BOOST_CLASS_EXPORT(Chrysalis::MovePointInstruction)
BOOST_CLASS_EXPORT(Chrysalis::BuildOutlineInstruction)
BOOST_CLASS_EXPORT(Chrysalis::RelativePointInstruction)
BOOST_CLASS_EXPORT(Chrysalis::UnfoldEdgeDartInstruction)
BOOST_CLASS_EXPORT(Chrysalis::IntersectionPointInstruction)

Project::Project(std::string name, ProjectSpace* space, PatternsContainer* patterns, ParametersContainer* parameters,
                 OptionsContainer* options, ExpressionsContainer* expressions, InstructionsContainer* instructions)
    : name_(std::move(name)), space_(space), options_(options), patterns_(patterns), parameters_(parameters),
      expressions_(expressions), instructions_(instructions), thread_([this](const std::stop_token& stopToken) -> void {
          std::unique_lock lock(mutex_);
          while (!stopToken.stop_requested()) {
              startExecution_.wait(lock, [&] -> bool {
                  return pendingExecution_ || stopToken.stop_requested() || !queue_.empty();
              });
              if (stopToken.stop_requested()) return;
              while (!queue_.empty()) {
                  auto task = std::move(queue_.front());
                  queue_.pop();
                  lock.unlock();
                  task();
                  lock.lock();
              }
              if (pendingExecution_) {
                  pendingExecution_ = false;
                  lock.unlock();
                  instructions_->execute();
                  lock.lock();
              }
          }
      }) {}

Project::~Project() {
    instructions_->ignore();
    thread_.request_stop();
    startExecution_.notify_one();
    thread_.join();
    
    delete space_;
    delete options_;
    delete patterns_;
    delete parameters_;
    delete expressions_;
    delete instructions_;
}

std::unique_ptr<Project> Project::create() {
    return create("Untitled");
}

std::unique_ptr<Project> Project::create(const std::string& name) {
    const auto globalOptions = new OptionsContainer();
    const auto globalExpressions = new ExpressionsContainer();
    return std::make_unique<Project>(
        name,
        new ProjectSpace(),
        new PatternsContainer(),
        new ParametersContainer(),
        globalOptions,
        globalExpressions,
        new InstructionsContainer(new OptionsContainer(globalOptions), new ExpressionsContainer(globalExpressions)));
}

std::vector<char> Project::bytes() const {
    std::vector<char> buffer;
    boost::iostreams::back_insert_device sink(buffer);
    boost::iostreams::stream os(sink);
    boost::archive::binary_oarchive archive(os);
    archive << this;
    return buffer;
}

std::unique_ptr<Project> Project::fromBytes(const char* bytes, const size_t size) {
    boost::iostreams::array_source source(bytes, size);
    boost::iostreams::stream is(source);
    boost::archive::binary_iarchive archive(is);
    Project* project = nullptr;
    try {
        archive >> project;
        return std::unique_ptr<Project>(project);
    } catch (const boost::archive::archive_exception &e) {
        delete project;
        throw ProjectIOError("Cannot read project from bytes");
    }
}

std::unique_ptr<Project> Project::read(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) throw ProjectIOError("Failed to open file: " + filePath);
    boost::archive::binary_iarchive archive(file);
    Project* project = nullptr;
    try {
        archive >> project;
        return std::unique_ptr<Project>(project);
    } catch (const boost::archive::archive_exception &e) {
        delete project;
        throw ProjectIOError("Cannot read file: " + filePath + ". Code #" + std::to_string(e.code) + ": " + e.what());
    }
}

void Project::write(const std::string& filePath, const Project& project) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw ProjectIOError("Failed to open file for write: " + filePath);
    }
    boost::archive::binary_oarchive archive(file);
    archive << &project;
    file.close();
    if (!file) throw ProjectIOError("Failed to save project into: " + filePath);
}

void Project::execute() {
    pendingExecution_ = true;
    startExecution_.notify_one();
}

void Project::onExecuted(const std::function<void()>& function) {
    {
        std::lock_guard lock(mutex_);
        queue_.push(function);
    }
    startExecution_.notify_one();
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
