find_package(clo-sdk REQUIRED)

file(GLOB_RECURSE CLO_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE CLO_UI_COMMON_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}include/clo-ui-common/*.h)

add_library(CloUI STATIC ${CLO_HEADERS} ${CLO_UI_COMMON_HEADERS})
target_include_directories(CloUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(CloUI PUBLIC clo-sdk::clo-sdk Qt5::Core Qt5::Widgets)

if (SAMPLES_EXTENSION)
    file(GLOB_RECURSE CLO_SAMPLES_H CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/samples/*.h)
    file(GLOB_RECURSE CLO_SAMPLES_CPP CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/samples/*.cpp)
    add_library(CloSamples STATIC ${CLO_SAMPLES_CPP} ${CLO_SAMPLES_H})
    target_include_directories(CloSamples PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/samples)
    target_link_libraries(CloSamples PUBLIC Core)
endif ()