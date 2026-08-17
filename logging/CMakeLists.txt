find_package(spdlog REQUIRED)

file(GLOB_RECURSE LOGGER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

if (APP STREQUAL "Chrysalis")
    add_library(LoggingLibrary STATIC ${LOGGER_SOURCES})
else ()
    add_library(LoggingLibrary SHARED ${LOGGER_SOURCES})
    target_compile_definitions(LoggingLibrary PUBLIC LOGGING_LIBRARY_SHARED)
    target_compile_definitions(LoggingLibrary PRIVATE LOGGING_LIBRARY_EXPORT)
endif ()

target_include_directories(LoggingLibrary PUBLIC include)
target_link_libraries(LoggingLibrary PUBLIC spdlog::spdlog)
target_compile_definitions(LoggingLibrary PUBLIC LOGS_DIR="${LOGS_DIR}" LOGS_FILE_NAME="${APP}")