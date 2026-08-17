file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
        ${CMAKE_CURRENT_SOURCE_DIR}/unit/*
)

add_executable(DevToolsExtensionTest main.cpp ${TEST_SOURCES})
target_include_directories(DevToolsExtensionTest PRIVATE include)
set_target_properties(DevToolsExtensionTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_TEST_OUTPUT_DIR})
target_link_libraries(DevToolsExtensionTest PRIVATE DevToolsExtensionObject GTest::gtest GTest::gmock)
add_dependencies(DevToolsExtensionTest CLO3DExtensionsTest)

if (WIN32)
    add_custom_command(TARGET DevToolsExtensionTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:DevToolsExtensionTest> $<TARGET_FILE_DIR:DevToolsExtensionTest>
            COMMAND_EXPAND_LISTS
    )
endif ()

add_test(NAME DevToolsExtensionTest COMMAND DevToolsExtensionTest)