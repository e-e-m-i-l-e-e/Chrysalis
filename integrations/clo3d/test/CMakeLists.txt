file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/unit/*)

add_executable(CLO3DExtensionsTest main.cpp ${TEST_SOURCES})
target_link_libraries(CLO3DExtensionsTest PRIVATE CLO3DExtensions GTest::gtest)
set_target_properties(CLO3DExtensionsTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_TEST_OUTPUT_DIR})

if (WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(QT_QOFFSCREEN_PLUGIN_NAME qoffscreend.dll)
    else ()
        set(QT_QOFFSCREEN_PLUGIN_NAME qoffscreen.dll)
    endif()
else ()
    set(QT_QOFFSCREEN_PLUGIN_NAME libqoffscreen.so)
endif ()

find_file(QT_QOFFSCREEN_PLUGIN NAMES ${QT_QOFFSCREEN_PLUGIN_NAME} PATHS ${CONAN_RUNTIME_LIB_DIRS} PATH_SUFFIXES ../plugins/platforms)
add_custom_command(
        TARGET CLO3DExtensionsTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:CLO3DExtensionsTest>/temp
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_QOFFSCREEN_PLUGIN} $<TARGET_FILE_DIR:CLO3DExtensionsTest>/platforms/${QT_QOFFSCREEN_PLUGIN_NAME}
        COMMENT "Copying qoffscreen.dll to test platforms directory"
)
add_test(NAME CLO3DExtensionsTest COMMAND CLO3DExtensionsTest)