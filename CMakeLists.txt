cmake_minimum_required(VERSION 3.28.3)

project(Chrysalis)

set(CMAKE_CXX_STANDARD 23)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/BuildArtifacts")
set(LOGS_DIR "${CMAKE_SOURCE_DIR}/.logs" CACHE PATH "Directory for log files")

if (LINUX)
    set(PYTHON "${CMAKE_SOURCE_DIR}/.python/venv-linux/bin/python" CACHE FILEPATH "Python interpreter" FORCE)

    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=address,undefined)

    add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
    add_link_options(--coverage)
else ()
    set(PYTHON "${CMAKE_SOURCE_DIR}/.python/venv/Scripts/python.exe" CACHE FILEPATH "Python interpreter" FORCE)
    add_compile_options(/Zc:preprocessor)
endif ()

include(CTest)
enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(.docs)
add_subdirectory(logging)
add_subdirectory(pattern)
add_subdirectory(renderer)

if (APP STREQUAL "Chrysalis")
    add_subdirectory(lab)
else ()
    add_subdirectory(integrations)
endif ()