cmake_minimum_required(VERSION 3.28.3)

project(Chrysalis)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile_commands.json" FORCE)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/BuildArtifacts" CACHE PATH "Output directory")
set(LOGS_DIR "${CMAKE_SOURCE_DIR}/.logs" CACHE PATH "Directory for log files")
list(APPEND CMAKE_PROGRAM_PATH "${CMAKE_SOURCE_DIR}/.misc")

if (LINUX)
    set(PYTHON_VENV_DIR "${CMAKE_SOURCE_DIR}/.python/venv-linux" CACHE PATH "Python virtual environment directory")
    set(PYTHON_VENV_BIN "${PYTHON_VENV_DIR}/bin")
    set(PYTHON "${PYTHON_VENV_BIN}/python" CACHE FILEPATH "Python interpreter" FORCE)

    set(SANITIZER "ASan" CACHE STRING "Sanitizer to use: ASan, TSan")
    if(SANITIZER STREQUAL "ASan")
        add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -g)
        add_link_options(-fsanitize=address,undefined)
        add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
        add_link_options(--coverage)
    elseif(SANITIZER STREQUAL "TSan")
        add_compile_options(-fsanitize=thread -fno-omit-frame-pointer -g)
        add_link_options(-fsanitize=thread)
    endif ()
else ()
    set(PYTHON_VENV_DIR "${CMAKE_SOURCE_DIR}/.python/venv")
    set(PYTHON_VENV_BIN "${PYTHON_VENV_DIR}/Scripts")
    set(PYTHON "${PYTHON_VENV_BIN}/python.exe" CACHE FILEPATH "Python interpreter" FORCE)

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