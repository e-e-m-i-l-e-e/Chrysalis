file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(ProjectComposerLibrary STATIC ${PROJECT_SOURCES})
target_include_directories(ProjectComposerLibrary PUBLIC include)
target_link_libraries(ProjectComposerLibrary PRIVATE PatternLibrary)