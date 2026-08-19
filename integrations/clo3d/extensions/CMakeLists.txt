set(CLO3D_EXTENSION_OUTPUT_DIR ${CLO3D_OUTPUT_DIR}/extensions)

function(add_clo3d_extension EXTENSION_NAME)
    set(EXTENSION_NAME ${EXTENSION_NAME}Extension)
    set(EXTENSION_OBJECT_TARGET ${EXTENSION_NAME}Core)

    file(GLOB_RECURSE EXTENSION_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
    file(GLOB_RECURSE EXTENSION_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

    add_library(${EXTENSION_OBJECT_TARGET} OBJECT ${EXTENSION_HEADERS} ${EXTENSION_SOURCES})
    set_target_properties(${EXTENSION_OBJECT_TARGET} PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")
    target_include_directories(${EXTENSION_OBJECT_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${EXTENSION_OBJECT_TARGET} PUBLIC CLO3DExtensionsCore)

    add_library(${EXTENSION_NAME} SHARED)
    target_link_libraries(${EXTENSION_NAME} PRIVATE ${EXTENSION_OBJECT_TARGET} CLO3DExtensions)
    set_target_properties(${EXTENSION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_EXTENSION_OUTPUT_DIR})

    if(WIN32)
        add_custom_command(TARGET ${EXTENSION_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${EXTENSION_NAME}> ${CLO_EXTENSION_HOME}/${EXTENSION_NAME}.dll
                COMMENT "Deploying ${EXTENSION_NAME}.dll to CLO3D extensions directory"
        )
    endif()
    add_subdirectory(test)
endfunction()

add_subdirectory(chrysalis)
add_subdirectory(dev-tools)
add_subdirectory(authenticator)