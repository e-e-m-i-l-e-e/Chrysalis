file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/integration/*)

add_executable(PatternLibraryTest ${TEST_SOURCES})
target_link_libraries(PatternLibraryTest PRIVATE PatternLibrary GTest::gtest GTest::gtest_main)
add_test(NAME PatternLibraryTest COMMAND PatternLibraryTest)