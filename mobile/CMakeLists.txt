set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED)

add_executable(QmlApp
        main.cpp
        qml.qrc
)

target_link_libraries(QmlApp
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
#        Qt6::Quick
#        Qt6::QuickControls2
)

add_custom_command(TARGET QmlApp POST_BUILD
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/../.conan/p/b/qt5f42820c94477/p/bin/windeployqt.exe"
        --no-translations
        --qmldir ${CMAKE_CURRENT_SOURCE_DIR}
        $<TARGET_FILE:QmlApp>
)
