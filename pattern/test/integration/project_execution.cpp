#include <gtest/gtest.h>

#include "Project.h"
#include "projects/Project1Composer.h"

#include "arguments/ParameterArgument.h"
#include "arguments/VectorFunctionArgument.h"

#include "instructions/FreePointInstruction.h"

using namespace Chrysalis;

class TestProject1: public ::testing::Test {
    static constexpr auto TEMP_FILE = "temp";
protected:
    void SetUp() override {
        project_ = std::unique_ptr<Project>(Project1Composer::createProject());
        Project1Composer(project_.get()).fill();

        project_->getInstructions()->execute();

        Project::write(TEMP_FILE, *project_);
        deserializedProject_ = Project::read(TEMP_FILE);
        deserializedProject_->getInstructions()->execute();
    }
    [[nodiscard]] std::vector<Project*> getProjects() const {
        return {project_.get(), deserializedProject_.get()};
    }
    static std::vector<std::pair<PatternSpace*, std::reference_wrapper<const std::unordered_map<std::string, std::pair<double, double>>>>> data(const Project* project) {
        return {
            std::make_pair(project->getPatterns()->get(Project1Composer::PatternName::BACK)->getSpace(), std::cref(Project1Composer::expectedBack)),
            std::make_pair(project->getPatterns()->get(Project1Composer::PatternName::FRONT)->getSpace(), std::cref(Project1Composer::expectedFront)),
        };
    }
    std::unique_ptr<Project> project_;
    std::unique_ptr<Project> deserializedProject_ = nullptr;
};

TEST_F(TestProject1, Project1) {
    for (const auto& project : getProjects()) {
        for (const auto& [patternSpace, expected]: data(project)) {
            ASSERT_EQ(patternSpace->getPoints().size(), expected.get().size());
            for (const auto& [name, point]: expected.get()) {
                ASSERT_TRUE(patternSpace->hasPoint(name));
                EXPECT_NEAR(patternSpace->getPoint(name)->x(), point.first, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
                EXPECT_NEAR(patternSpace->getPoint(name)->y(), point.second, pow(10, -4)) << "x coordinate of point \"" << name << "\" is misplaced.";
            }
        }
    }
}