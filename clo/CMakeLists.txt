find_package(clo-sdk REQUIRED)

file(GLOB_RECURSE CLO_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE CLO_UI_COMMON_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}include/clo-ui-common/*.h)

add_library(CloUI STATIC ${CLO_HEADERS} ${CLO_UI_COMMON_HEADERS})
target_include_directories(CloUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(CloUI PUBLIC clo-sdk::clo-sdk Qt5::Core Qt5::Widgets)

if (SAMPLES_EXTENSION)
    file(GLOB_RECURSE CLO_SAMPLES_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/samples/*.cpp)
    file(GLOB_RECURSE CLO_SAMPLES_H   CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/samples/*.h)
    set(CLO_SAMPLES_SRC     ${CLO_SAMPLES_SRC}                          PARENT_SCOPE)
    set(CLO_SAMPLES_H       ${CLO_SAMPLES_H}                            PARENT_SCOPE)
    set(CLO_SAMPLES_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/samples         PARENT_SCOPE)
endif ()