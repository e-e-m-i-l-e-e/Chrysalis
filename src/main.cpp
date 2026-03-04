#include <iostream>
#include <QString>
#include <polyhook2/Detour/ADetour.hpp>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << QString("Test").isSimpleText() << std::endl;
    return 0;
}