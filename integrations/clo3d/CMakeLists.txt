set(CLO3D_OUTPUT_DIR ${OUTPUT_DIR}/CLO3D)
set(CLO3D_TEST_OUTPUT_DIR ${CLO3D_OUTPUT_DIR}/Test)
set(CLO3D_TEST_TEMP_DIR ${CLO3D_TEST_OUTPUT_DIR}/temp)
file(MAKE_DIRECTORY ${CLO3D_TEST_TEMP_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED)

add_subdirectory(widgets)

if (WIN32)
    # ----- Build "Launcher.exe" ---------------------------------------------------------------------------------------
    set(CLO_HOME "C:/Program Files/CLO Standalone OnlineAuth" CACHE STRING "Folder where CLO3D is installed")

    add_executable(Launcher CLO3DLauncher.cpp)
    set_target_properties(Launcher PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_OUTPUT_DIR})
    target_link_libraries(Launcher PRIVATE LoggingLibrary)
else ()
    set(CLO_HOME ${CLO3D_TEST_OUTPUT_DIR}/temp CACHE STRING "Folder where CLO3D is installed")
endif ()
set(CLO_EXTENSION_HOME ${CLO_HOME}/extensions CACHE STRING "Folder where CLO3D extensions are located")

add_compile_definitions(CLO_HOME="${CLO_HOME}")
add_compile_definitions(CLO_EXTENSION_HOME="${CLO_EXTENSION_HOME}")

message("CLO_HOME is set to ${CLO_HOME}")

# ----- Build CLO3DExtensions ------------------------------------------------------------------------------------------

file(GLOB_RECURSE CLO3D_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
file(GLOB_RECURSE CLO3D_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(CLO3DExtensionsCore OBJECT resources/resources.qrc ${CLO3D_HEADERS} ${CLO3D_SOURCES})
set_target_properties(CLO3DExtensionsCore PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")
target_include_directories(CLO3DExtensionsCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(CLO3DExtensionsCore PUBLIC
        LoggingLibrary PatternLibrary CLO3DWidgetsLibrary HooksLibrary
        Qt5::Core Qt5::CorePrivate Qt5::Concurrent Qt5::Network Qt5::Xml Qt5::Designer)
find_package(clo-sdk REQUIRED)
if (WIN32)
    target_link_libraries(CLO3DExtensionsCore PUBLIC clo-sdk::clo-sdk)
else ()
    add_subdirectory(linux)
    target_link_libraries(CLO3DExtensionsCore PUBLIC CLOSDKStubs)
endif ()
target_compile_definitions(CLO3DExtensionsCore PRIVATE CLO3D_EXTENSION_EXPORT)

if(WIN32)
    add_library(CLO3DExtensions SHARED CLO3DExtensions.cpp)
else ()
    add_library(CLO3DExtensions SHARED)
endif ()
target_link_libraries(CLO3DExtensions PUBLIC CLO3DExtensionsCore)
set_target_properties(CLO3DExtensions PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_OUTPUT_DIR})

if (WIN32)
    add_custom_command(TARGET CLO3DExtensions POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CLO3DExtensions> $<TARGET_FILE_DIR:CLO3DExtensions>
            COMMAND_EXPAND_LISTS
    )
    add_custom_command(TARGET CLO3DExtensions POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:CLO3DExtensions> "${CLO_HOME}/CLO3DExtensions.dll"
            COMMENT "Deploying CLO3DExtensions.dll to CLO directory"
    )
endif ()

# ----- Build tests ----------------------------------------------------------------------------------------------------

add_subdirectory(test)

# ----- Build extensions -----------------------------------------------------------------------------------------------

add_subdirectory(extensions)

# ----- Build development tools ----------------------------------------------------------------------------------------

add_subdirectory(tools)

# ----------------------------------------------------------------------------------------------------------------------