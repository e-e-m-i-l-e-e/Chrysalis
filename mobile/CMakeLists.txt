set(QT_QML_GENERATE_AOTSTATS OFF)

find_package(Qt6 REQUIRED)
qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

# ── Source files ─────────────────────────────────────────────────────────────
set(SOURCES
        main.cpp
        openglitem.cpp
)

set(HEADERS
        openglitem.h
)

# ── QML files registered as a module ─────────────────────────────────────────
qt_add_executable(QtOpenGLApp
        ${SOURCES}
        ${HEADERS}
)

qt_add_qml_module(QtOpenGLApp
        URI QtOpenGLApp
        VERSION 1.0
        QML_FILES
        Main.qml
)

# ── Link Qt modules ───────────────────────────────────────────────────────────
target_link_libraries(QtOpenGLApp PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::OpenGL
)

qt_import_qml_plugins(QtOpenGLApp)
add_custom_command(TARGET QtOpenGLApp POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
        --qmldir "${CMAKE_SOURCE_DIR}/mobile"
        --no-translations
        "$<TARGET_FILE:QtOpenGLApp>"
        COMMENT "Deploying Qt runtime with windeployqt"
)