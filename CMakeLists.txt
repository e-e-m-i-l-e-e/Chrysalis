cmake_minimum_required(VERSION 3.28.3)

project(FashionDesignApps)

set(CMAKE_CXX_STANDARD 20)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/BuildArtifacts")
set(LOGS_DIR "${CMAKE_SOURCE_DIR}/.logs" CACHE PATH "Directory for log files")

add_subdirectory(logging)
add_subdirectory(pattern-builder)

if (APP STREQUAL "mobile")
    add_subdirectory(mobile)
else ()
    add_subdirectory(integrations)
endif ()