set(CMAKE_AUTOMOC ON)
set(QT_QML_GENERATE_AOTSTATS OFF)

find_package(Qt6 REQUIRED)
qt_standard_project_setup()

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
        Qt6::Quick2Plugin
        Qt6::QWindowsIntegrationPlugin
)

qt_import_qml_plugins(QmlApp)
qt_finalize_executable(QmlApp)