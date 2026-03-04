cmake_minimum_required(VERSION 4.1.2)
project(CLOExtensions)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt5 REQUIRED)
find_package(polyhook2 REQUIRED)

add_executable(CLOExtensions src/main.cpp)
target_link_libraries(CLOExtensions PRIVATE Qt5::Core polyhook2::polyhook2)

add_custom_command(TARGET CLOExtensions POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:CLOExtensions>
        $<TARGET_FILE_DIR:CLOExtensions>
        COMMAND_EXPAND_LISTS
)