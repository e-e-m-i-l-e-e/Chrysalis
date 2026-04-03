cmake_minimum_required(VERSION 4.1.2)

project(CLOExtensions)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CLO_HOME "C:/Program Files/CLO Standalone OnlineAuth" CACHE STRING "Folder where CLO3D is installed")
set(LOGS_DIR "${CMAKE_SOURCE_DIR}/.logs" CACHE PATH "Directory for log files")

option(SAMPLES_EXTENSION "Samples Extension" OFF)

add_compile_definitions(CLO_HOME="${CLO_HOME}")
message("CLO_HOME is set to ${CLO_HOME}")

add_subdirectory(interfaces)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE Logger)

find_package(Qt5 REQUIRED)

add_subdirectory(clo)
add_subdirectory(pattern-builder)
add_subdirectory(core)

add_library(Extensions SHARED resources/resources.qrc extensions.cpp)
target_link_libraries(Extensions PRIVATE HooksManager Core)

add_subdirectory(test)

add_custom_command(TARGET Extensions POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Extensions>
        $<TARGET_FILE_DIR:Extensions>
        COMMAND_EXPAND_LISTS
)

add_custom_command(TARGET Extensions POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Extensions>
        "${CLO_HOME}/Extensions.dll"
        COMMENT "Deploying Extensions.dll to CLO directory"
)

add_subdirectory(qt-designer-plugin)