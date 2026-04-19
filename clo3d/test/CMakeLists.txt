find_package(GTest REQUIRED)

add_executable(Test HooksManager.cpp)
target_link_libraries(Test PRIVATE GTest::gtest_main HooksManager)

add_custom_command(TARGET Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Test>
        $<TARGET_FILE_DIR:Test>
        COMMAND_EXPAND_LISTS
)