add_executable(CLO3DExtensionsTest)
target_link_libraries(CLO3DExtensionsTest PRIVATE CLO3DExtensionsBase GTest::gtest_main GTest::gtest)
set_target_properties(CLO3DExtensionsTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_TEST_OUTPUT_DIR})
find_file(QT_QOFFSCREEN_PLUGIN NAMES qoffscreen.dll PATHS ${CONAN_RUNTIME_LIB_DIRS} PATH_SUFFIXES ../plugins/platforms)
add_custom_command(
        TARGET CLO3DExtensionsTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:CLO3DExtensionsTest>/temp
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_QOFFSCREEN_PLUGIN} $<TARGET_FILE_DIR:CLO3DExtensionsTest>/platforms/qoffscreen.dll
        COMMENT "Copying qoffscreen.dll to test platforms directory"
)
add_test(NAME CLO3DExtensionsTest COMMAND CLO3DExtensionsTest)