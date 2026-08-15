set(CLO3D_OUTPUT_DIR ${OUTPUT_DIR}/CLO3D)
set(CLO3D_TEST_OUTPUT_DIR ${CLO3D_OUTPUT_DIR}/Test)

option(EXTEND_WITH_CHRYSALIS "Add \"Chrysalis Extension\"" ON)
option(EXTEND_WITH_AUTHENTICATOR "Skip authentication with \"CLOSET\"" ON)
option(EXTEND_WITH_DEV_TOOLS "Add options and settings useful for debugging and investigation" ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED)

add_subdirectory(widgets)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")

    # ----- Build "Launcher.exe" ---------------------------------------------------------------------------------------

    set(CLO_HOME "C:/Program Files/CLO Standalone OnlineAuth" CACHE STRING "Folder where CLO3D is installed")

    add_compile_definitions(CLO_HOME="${CLO_HOME}")
    message("CLO_HOME is set to ${CLO_HOME}")

    add_executable(Launcher CLO3DLauncher.cpp)
    set_target_properties(Launcher PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_OUTPUT_DIR})
    target_link_libraries(Launcher PRIVATE LoggingLibrary)

    # ----- Build "Extensions.dll" -------------------------------------------------------------------------------------

    # Prepare requested extensions

    set(CLO3D_UI_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
    set(CLO3D_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
    file(GLOB_RECURSE CLO3D_SOURCES CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/include/*
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*
    )
    add_subdirectory(extensions)

    # Build CLO3DExtensions.dll
    add_library(CLO3DExtensionsBase OBJECT resources/resources.qrc CLO3DExtensions.cpp ${CLO3D_SOURCES})
    set_target_properties(CLO3DExtensionsBase PROPERTIES AUTOUIC_SEARCH_PATHS "${CLO3D_UI_DIRS}")
    target_include_directories(CLO3DExtensionsBase PUBLIC ${CLO3D_INCLUDE_DIRS})
    target_compile_definitions(CLO3DExtensionsBase PUBLIC
            EXTEND_WITH_CHRYSALIS=$<BOOL:${EXTEND_WITH_CHRYSALIS}>
            EXTEND_WITH_DEV_TOOLS=$<BOOL:${EXTEND_WITH_DEV_TOOLS}>
            EXTEND_WITH_AUTHENTICATOR=$<BOOL:${EXTEND_WITH_AUTHENTICATOR}>
    )
    target_link_libraries(CLO3DExtensionsBase PUBLIC
            LoggingLibrary PatternLibrary CLO3DWidgetsLibrary HooksLibrary
            Qt5::Core Qt5::CorePrivate Qt5::Concurrent Qt5::Xml Qt5::Designer)
    if (WIN32)
        find_package(clo-sdk REQUIRED)
        target_link_libraries(CLO3DExtensionsBase PUBLIC clo-sdk::clo-sdk)
    endif ()

    add_library(CLO3DExtensions SHARED $<TARGET_OBJECTS:CLO3DExtensionsBase>)
    target_link_libraries(CLO3DExtensions PUBLIC CLO3DExtensionsBase)
    set_target_properties(CLO3DExtensions PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_OUTPUT_DIR})

    add_custom_command(TARGET CLO3DExtensions POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CLO3DExtensions> $<TARGET_FILE_DIR:CLO3DExtensions>
            COMMAND_EXPAND_LISTS
    )

    add_custom_command(TARGET CLO3DExtensions POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:CLO3DExtensions> "${CLO_HOME}/CLO3DExtensions.dll"
            COMMENT "Deploying CLO3DExtensions.dll to CLO directory"
    )

endif ()

# ----- Build development tools ----------------------------------------------------------------------------------------

add_subdirectory(tools)

# ----- Build tests ----------------------------------------------------------------------------------------------------

add_subdirectory(test)

# ----------------------------------------------------------------------------------------------------------------------