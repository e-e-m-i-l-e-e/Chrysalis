set(QT_QML_GENERATE_AOTSTATS OFF)

find_package(Qt6 REQUIRED)
qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

qt_add_executable(PatternBuilderApp main.cpp ${SOURCES})
qt_add_resources(PatternBuilderApp shaders PREFIX "/" FILES shaders/vertex.vert shaders/fragment.frag)
qt_add_qml_module(PatternBuilderApp URI PatternBuilder VERSION 1.0 QML_FILES qml/Main.qml)
target_include_directories(PatternBuilderApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PatternBuilderApp PRIVATE Logger Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::OpenGL PatternBuilder)
qt_import_qml_plugins(PatternBuilderApp)

add_custom_command(TARGET PatternBuilderApp POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
        --qmldir "${CMAKE_SOURCE_DIR}/mobile"
        --no-translations
        "$<TARGET_FILE:PatternBuilderApp>"
        COMMENT "Deploying Qt runtime with windeployqt"
)