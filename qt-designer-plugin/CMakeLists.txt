add_library(myplugin SHARED
        TabularInputPlugin.h TabularInputPlugin.cpp
        ${PATTERN_BUILDER_WIDGETS_SRC} ${PATTERN_BUILDER_WIDGETS_H}
)
set_target_properties(myplugin PROPERTIES AUTOUIC_SEARCH_PATHS "${PATTERN_BUILDER_UI}")
target_include_directories(myplugin PUBLIC ${PATTERN_BUILDER_INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(myplugin PRIVATE Qt5::Widgets Qt5::UiPlugin)