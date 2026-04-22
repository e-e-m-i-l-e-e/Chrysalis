cmake_minimum_required(VERSION 4.1.2)

project(FashionDesignApps)

set(CMAKE_CXX_STANDARD 20)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/output/${CMAKE_BUILD_TYPE}")
set(LOGS_DIR "${CMAKE_SOURCE_DIR}/.logs" CACHE PATH "Directory for log files")

add_subdirectory(common)

if(APP STREQUAL "CLO3D")
    # CLO3D extensions cannot be build in Debug mode. RelWithDebInfo is used instead.
    add_subdirectory(clo3d)
elseif (APP STREQUAL "mobile")
    # Regular Debug mode can be used.
    add_subdirectory(mobile)
endif ()