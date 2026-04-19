find_package(GTest REQUIRED)

add_executable(Clo3DTests HooksManager.cpp)
set_target_properties(Clo3DTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/test")
target_link_libraries(Clo3DTests PRIVATE GTest::gtest_main HooksManager)
add_custom_command(TARGET Clo3DTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:Clo3DTests> $<TARGET_FILE_DIR:Clo3DTests>
        COMMAND_EXPAND_LISTS)