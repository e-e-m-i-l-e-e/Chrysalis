find_package(GTest REQUIRED)

add_executable(CLO3DTests HooksManager.cpp)
target_link_libraries(CLO3DTests PRIVATE GTest::gtest_main polyhook2::polyhook2)
add_custom_command(TARGET CLO3DTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CLO3DTests> $<TARGET_FILE_DIR:CLO3DTests>
        COMMAND_EXPAND_LISTS)