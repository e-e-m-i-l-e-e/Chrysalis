find_package(CGAL REQUIRED)

file(GLOB_RECURSE PATTERN_BUILDER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(PatternLibrary STATIC ${PATTERN_BUILDER_SOURCES})
target_include_directories(PatternLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PatternLibrary PUBLIC CGAL::CGAL)