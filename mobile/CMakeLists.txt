find_package(Qt6 REQUIRED)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

set(QT_QML_GENERATE_AOTSTATS OFF)

qt_standard_project_setup()

add_subdirectory(qml/FigmaStyle)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

qt_add_executable(PatternBuilderApp main.cpp ${SOURCES})
qt_add_resources(PatternBuilderApp logo PREFIX "/" FILES logo.png)
qt_add_resources(PatternBuilderApp shaders PREFIX "/" FILES shaders/vertex.vert shaders/fragment.frag)
qt_add_qml_module(PatternBuilderApp URI PatternBuilder VERSION 1.0 QML_FILES qml/ChrysalisLab.qml qml/ChrysalisLabWelcomeContent.qml RESOURCES qml/FigmaStyle/dark/images/busyindicator-indicator.png)
target_include_directories(PatternBuilderApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PatternBuilderApp PRIVATE Logger Qt6::Core Qt6::Gui Qt6::Qml Qt6::OpenGL PatternBuilder FigmaStyle)
qt_import_qml_plugins(PatternBuilderApp)

add_custom_command(TARGET PatternBuilderApp POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
        --qmldir "${CMAKE_SOURCE_DIR}/mobile"
        --no-translations
        "$<TARGET_FILE:PatternBuilderApp>"
        COMMENT "Deploying Qt runtime with windeployqt"
)