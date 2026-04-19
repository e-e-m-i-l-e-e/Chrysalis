file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(CORE_SOURCES ${SRC} ${PATTERN_BUILDER_SRC} ${PATTERN_BUILDER_H}
        include/ExtensionsSettings.h
include/MVDockingButton.h include/MVDockWidgetTitleBar.h include/MVDockWidgetTitleBarBase.h)

find_package(clo-sdk REQUIRED)

add_library(Core STATIC)
target_sources(Core PRIVATE ${CORE_SOURCES})
set_target_properties(Core PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui;${PATTERN_BUILDER_UI}")
target_include_directories(Core PUBLIC include ${PATTERN_BUILDER_INCLUDE})
target_link_libraries(Core PUBLIC Logger HooksManager clo-sdk::clo-sdk Qt5::Designer Qt5::Xml Qt5::Concurrent Qt5::Network Qt5::CorePrivate UI)