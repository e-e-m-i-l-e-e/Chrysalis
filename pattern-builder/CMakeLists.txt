file(GLOB_RECURSE PATTERN_BUILDER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

find_package(CGAL REQUIRED)
add_library(PatternBuilder STATIC ${PATTERN_BUILDER_SOURCES})
target_include_directories(PatternBuilder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PatternBuilder PUBLIC CGAL::CGAL)

add_executable(PatternBuilderEXE main.cpp)
target_link_libraries(PatternBuilderEXE PRIVATE PatternBuilder)