find_package(Qt6 REQUIRED)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

set(QT_QML_GENERATE_AOTSTATS OFF)

qt_standard_project_setup()

add_subdirectory(qml/FigmaStyle)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

qt_add_executable(ChrysalisLab main.cpp ${SOURCES})
qt_add_resources(ChrysalisLab logo PREFIX "/" FILES logo.png)
qt_add_resources(ChrysalisLab fonts PREFIX "/" FILES fonts/IBMPlexSans-Italic-VariableFont_wdth,wght.ttf fonts/IBMPlexSans-VariableFont_wdth,wght.ttf)
qt_add_qml_module(ChrysalisLab URI PatternBuilder VERSION 1.0
        QML_FILES
        qml/ChrysalisLab.qml
        qml/ChrysalisLabMenuBar.qml

        qml/ChrysalisProjectData.qml
        qml/ChrysalisPatternParameters.qml
        qml/ChrysalisLabWelcomeContent.qml
        qml/BaseChrysalisPatternFileDialog.qml
        qml/ChrysalisPatternOpenFileDialog.qml
        qml/ChrysalisPatternSaveFileDialog.qml
        RESOURCES
        qml/FigmaStyle/dark/images/busyindicator-indicator.png)
target_include_directories(ChrysalisLab PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ChrysalisLab PRIVATE PatternRendererLibrary ProjectComposerLibrary FigmaStyle Qt6::Core Qt6::Gui Qt6::Qml Qt6::OpenGL)

add_custom_command(TARGET ChrysalisLab POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
        --qmldir "${CMAKE_SOURCE_DIR}/lab"
        --no-translations
        "$<TARGET_FILE:ChrysalisLab>"
        COMMENT "Deploying Chrysalis Lab with windeployqt"
)