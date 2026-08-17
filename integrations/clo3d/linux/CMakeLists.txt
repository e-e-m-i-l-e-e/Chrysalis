file(GLOB_RECURSE CLO_SDK_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(CLOSDKStubs ${CLO_SDK_SOURCES})
target_include_directories(CLOSDKStubs PUBLIC ${clo-sdk_INCLUDE_DIR} ${clo-sdk_INCLUDE_DIR}/include)