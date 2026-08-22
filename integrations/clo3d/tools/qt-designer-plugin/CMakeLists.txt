file(GLOB_RECURSE QT_DESIGNER_PLUGIN_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

add_library(CLO3DQtDesignerPlugin SHARED ${QT_DESIGNER_PLUGIN_SOURCES})

if (WIN32)
    find_program(QT_DESIGNER_EXE NAMES designer.exe PATHS ${CONAN_RUNTIME_LIB_DIRS} PATH_SUFFIXES bin NO_DEFAULT_PATH)
    find_program(QT_WINDEPLOYQT_EXE NAMES windeployqt.exe PATHS ${CONAN_RUNTIME_LIB_DIRS} PATH_SUFFIXES bin NO_DEFAULT_PATH)

    set(QT_DESIGNER_RUNTIME_DIR ${OUTPUT_DIR}/CLO3DQtDesigner)
    add_custom_command(TARGET CLO3DQtDesignerPlugin POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${QT_DESIGNER_RUNTIME_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_DESIGNER_EXE}" "${QT_DESIGNER_RUNTIME_DIR}/designer.exe"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:LoggingLibrary> "${QT_DESIGNER_RUNTIME_DIR}"
            COMMAND_EXPAND_LISTS)
    add_custom_command(TARGET CLO3DQtDesignerPlugin POST_BUILD
            COMMAND "${QT_WINDEPLOYQT_EXE}" --dir "${QT_DESIGNER_RUNTIME_DIR}" --no-compiler-runtime "${QT_DESIGNER_RUNTIME_DIR}/designer.exe")
endif ()

set_target_properties(CLO3DQtDesignerPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${QT_DESIGNER_RUNTIME_DIR}/plugins/designer")
target_include_directories(CLO3DQtDesignerPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(CLO3DQtDesignerPlugin PRIVATE LoggingLibrary CLO3DWidgetsLibrary Qt5::Designer)