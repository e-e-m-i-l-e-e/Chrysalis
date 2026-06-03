set(SHADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${SHADERS_DIR})

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/shaders/.generator.py ${SHADERS_DIR} OUTPUT_VARIABLE SHADERS_HEADERS)
add_custom_target(Shaders DEPENDS ${SHADERS_HEADERS})

find_package(glm REQUIRED)
find_package(glad REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE RENDERER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(PatternRendererLibrary STATIC ${RENDERER_SOURCES})
target_include_directories(PatternRendererLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SHADERS_DIR})
target_link_libraries(PatternRendererLibrary PUBLIC LoggingLibrary PatternLibrary OpenGL::GL glad::glad glm::glm)
add_dependencies(PatternRendererLibrary Shaders)