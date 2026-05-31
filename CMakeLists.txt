cmake_minimum_required(VERSION 3.28.3)

project(Chrysalis)

set(CMAKE_CXX_STANDARD 23)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/BuildArtifacts")
set(LOGS_DIR "${CMAKE_SOURCE_DIR}/.logs" CACHE PATH "Directory for log files")

add_compile_options(/Zc:preprocessor)

find_package(GTest REQUIRED)

add_subdirectory(logging)
add_subdirectory(pattern)

if (APP STREQUAL "Chrysalis")
    add_subdirectory(lab)
else ()
    add_subdirectory(integrations)
endif ()