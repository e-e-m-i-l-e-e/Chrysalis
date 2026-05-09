set(QT_QML_GENERATE_AOTSTATS OFF)

find_package(Qt6 REQUIRED)
qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

qt_add_executable(QmlApp
        main.cpp
)

qt_add_qml_module(QmlApp
        URI QmlApp
        VERSION 1.0
        QML_FILES
        Main.qml
)

target_link_libraries(QmlApp PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

qt_import_qml_plugins(QmlApp)
add_custom_command(TARGET QmlApp POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
        --qmldir "${CMAKE_SOURCE_DIR}/mobile"
        --no-translations
        "$<TARGET_FILE:QmlApp>"
        COMMENT "Deploying Qt runtime with windeployqt"
)