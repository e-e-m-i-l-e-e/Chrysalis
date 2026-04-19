find_package(Qt5 REQUIRED)

add_executable(QmlApp
        main.cpp
        qml.qrc
)

target_link_libraries(QmlApp
        Qt5::Core
        Qt5::Gui
        Qt5::Qml
        Qt5::Quick
        Qt5::QuickControls2
)

add_custom_command(TARGET QmlApp POST_BUILD
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/../.conan/p/b/qtedf3f6075b0fb/p/bin/windeployqt.exe"
        --no-translations
        --qmldir ${CMAKE_CURRENT_SOURCE_DIR}
        $<TARGET_FILE:QmlApp>
)
