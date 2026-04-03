add_library(myplugin SHARED
        TabularInputPlugin.h TabularInputPlugin.cpp
)
target_include_directories(myplugin PUBLIC ${PATTERN_BUILDER_INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(myplugin PRIVATE Qt5::Widgets Qt5::UiPlugin)