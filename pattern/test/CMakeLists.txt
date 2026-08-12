file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
        ${CMAKE_CURRENT_SOURCE_DIR}/unit/*
        ${CMAKE_CURRENT_SOURCE_DIR}/integration/*
)

add_executable(PatternLibraryTest ${TEST_SOURCES})
target_include_directories(PatternLibraryTest PRIVATE include)
target_link_libraries(PatternLibraryTest PRIVATE ProjectComposerLibrary GTest::gtest_main GTest::gtest GTest::gmock)
add_test(NAME PatternLibraryTest COMMAND PatternLibraryTest --gtest_repeat=50)