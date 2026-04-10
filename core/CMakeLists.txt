file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(CORE_SOURCES ${SRC} ${PATTERN_BUILDER_SRC} ${PATTERN_BUILDER_H} include/ExtensionsSettings.h)

add_library(Core STATIC)

if (SAMPLES_EXTENSION)
    list(APPEND CORE_SOURCES ${CLO_SAMPLES_SRC} ${CLO_SAMPLES_H})
    target_include_directories(Core PUBLIC ${CLO_SAMPLES_INCLUDE})
    target_compile_definitions(Core PUBLIC SAMPLES_EXTENSION)
endif ()

target_sources(Core PRIVATE ${CORE_SOURCES})
set_target_properties(Core PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui;${PATTERN_BUILDER_UI}")
target_include_directories(Core PUBLIC include ${PATTERN_BUILDER_INCLUDE})
target_link_libraries(Core PUBLIC Logger HooksManager CloUI Qt5::Designer Qt5::Xml Qt5::Concurrent Qt5::Network UI)