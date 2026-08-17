find_package(polyhook2 REQUIRED)

file(GLOB_RECURSE HOOKS_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(HooksLibrary STATIC ${HOOKS_SOURCES})
target_include_directories(HooksLibrary PUBLIC include)
target_link_libraries(HooksLibrary PUBLIC LoggingLibrary polyhook2::polyhook2)