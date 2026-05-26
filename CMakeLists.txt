cmake_minimum_required(VERSION 3.28.3)

project(FashionDesignApps)

set(CMAKE_CXX_STANDARD 20)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/output")
set(LOGS_DIR "${CMAKE_SOURCE_DIR}/.logs" CACHE PATH "Directory for log files")

add_subdirectory(logger)
add_subdirectory(common)
add_subdirectory(pattern-builder)

if(APP STREQUAL "CLO3D")
    # CLO3D extensions cannot be build in Debug mode. RelWithDebInfo is used instead.
    add_subdirectory(clo3d)
elseif (APP STREQUAL "mobile")
    # Regular Debug mode can be used.
    add_subdirectory(mobile)
endif ()