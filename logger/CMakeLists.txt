find_package(spdlog REQUIRED)

file(GLOB_RECURSE LOGGER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(Logger STATIC ${LOGGER_SOURCES})
target_include_directories(Logger PUBLIC include)
target_link_libraries(Logger PUBLIC spdlog::spdlog)
target_compile_definitions(Logger PRIVATE LOGS_DIR="${LOGS_DIR}")