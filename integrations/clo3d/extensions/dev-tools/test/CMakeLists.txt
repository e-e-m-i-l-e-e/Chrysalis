file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
        ${CMAKE_CURRENT_SOURCE_DIR}/unit/*
)

add_executable(CLO3DDevToolsTest main.cpp ${TEST_SOURCES})
target_include_directories(CLO3DDevToolsTest PRIVATE include)
set_target_properties(CLO3DDevToolsTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_TEST_OUTPUT_DIR})
target_link_libraries(CLO3DDevToolsTest PRIVATE CLO3DExtensionsBase GTest::gtest GTest::gmock)
add_dependencies(CLO3DDevToolsTest CLO3DExtensionsTest)

add_custom_command(TARGET CLO3DDevToolsTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CLO3DDevToolsTest> $<TARGET_FILE_DIR:CLO3DDevToolsTest>
        COMMAND_EXPAND_LISTS
)

add_test(NAME CLO3DDevToolsTest COMMAND CLO3DDevToolsTest)