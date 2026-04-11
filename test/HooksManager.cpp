#include <gtest/gtest.h>

#include "HooksManager.h"

class TestClass {
    TestClass() = default;
    TestClass(int a, char b) {};
};

TEST(Constructors, DefaultConstructor) {
    HooksManager::addBefore<&TestClass::TestClass>([](HookHandle& handle, int& a, char&b) {});
    EXPECT_EQ(0, 0);
}