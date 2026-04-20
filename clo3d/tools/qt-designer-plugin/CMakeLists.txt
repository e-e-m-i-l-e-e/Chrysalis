find_program(QT_DESIGNER_EXE NAMES designer.exe PATHS ${CONAN_RUNTIME_LIB_DIRS} PATH_SUFFIXES bin NO_DEFAULT_PATH)
find_program(QT_WINDEPLOYQT_EXE NAMES windeployqt.exe PATHS ${CONAN_RUNTIME_LIB_DIRS} PATH_SUFFIXES bin NO_DEFAULT_PATH)

file(GLOB_RECURSE QT_DESIGNER_PLUGIN_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

add_library(QtDesignerPlugin SHARED ${QT_DESIGNER_PLUGIN_SOURCES})

set(QT_DESIGNER_RUNTIME_DIR ${OUTPUT_DIR}/qt-designer)
add_custom_command(TARGET QtDesignerPlugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${QT_DESIGNER_RUNTIME_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_DESIGNER_EXE}" "${QT_DESIGNER_RUNTIME_DIR}/designer.exe")
add_custom_command(TARGET QtDesignerPlugin POST_BUILD
        COMMAND "${QT_WINDEPLOYQT_EXE}" --dir "${QT_DESIGNER_RUNTIME_DIR}" --no-compiler-runtime "${QT_DESIGNER_RUNTIME_DIR}/designer.exe")
set_target_properties(QtDesignerPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${QT_DESIGNER_RUNTIME_DIR}/plugins/designer")
target_include_directories(QtDesignerPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(QtDesignerPlugin PRIVATE Logger Widgets Qt5::Designer)