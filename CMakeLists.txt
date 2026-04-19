cmake_minimum_required(VERSION 4.1.2)

project(FashionDesignApps)

set(CMAKE_CXX_STANDARD 20)

set(LOGS_DIR "${CMAKE_SOURCE_DIR}/.logs" CACHE PATH "Directory for log files")

add_subdirectory(common)
add_subdirectory(clo3d)
add_subdirectory(mobile)