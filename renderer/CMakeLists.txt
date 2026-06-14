set(SHADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${SHADERS_DIR})
file(GLOB_RECURSE SHADERS_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*)

add_custom_command(
        OUTPUT ${SHADERS_DIR}/.stamp
        COMMAND ${PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/shaders/.generator.py ${SHADERS_DIR}
        DEPENDS ${SHADER_SOURCES}
)

add_custom_target(Shaders ALL DEPENDS ${SHADERS_DIR}/.stamp)

find_package(glm REQUIRED)
find_package(glad REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE RENDERER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(PatternRendererLibrary STATIC ${RENDERER_SOURCES})
target_include_directories(PatternRendererLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SHADERS_DIR})
target_link_libraries(PatternRendererLibrary PUBLIC LoggingLibrary PatternLibrary OpenGL::GL glad::glad glm::glm)
add_dependencies(PatternRendererLibrary Shaders)