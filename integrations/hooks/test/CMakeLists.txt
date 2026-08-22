file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/unit/*)

add_executable(HooksTest ${TEST_SOURCES})
target_include_directories(HooksTest PRIVATE include)
target_link_libraries(HooksTest PRIVATE GTest::gtest_main GTest::gtest HooksLibrary)

if (WIN32)
    add_custom_command(TARGET HooksTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:HooksLibrary> $<TARGET_FILE_DIR:HooksTest>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:LoggingLibrary> $<TARGET_FILE_DIR:HooksTest>
            COMMAND_EXPAND_LISTS)
endif ()
add_test(NAME HooksTest COMMAND HooksTest)