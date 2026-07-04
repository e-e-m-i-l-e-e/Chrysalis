find_package(CGAL REQUIRED)
find_package(tinyspline REQUIRED)

file(GLOB_RECURSE PATTERN_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(PatternLibrary STATIC ${PATTERN_SOURCES})
target_include_directories(PatternLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PatternLibrary PUBLIC CGAL::CGAL tinysplinecxx::tinysplinecxx)

add_subdirectory(composer)
add_subdirectory(test)