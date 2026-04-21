set(CLO3D_OUTPUT_DIR "${OUTPUT_DIR}/CLO3D")

option(EXTEND_WITH_AUTHENTICATOR "Skip authentication with \"CLOSET\"" ON)
option(EXTEND_WITH_PATTERN_BUILDER "Add \"Pattern Builder Extension\"" ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ----- Build "Launcher.exe" -------------------------------------------------------------------------------------------

set(CLO_HOME "C:/Program Files/CLO Standalone OnlineAuth" CACHE STRING "Folder where CLO3D is installed")

add_compile_definitions(CLO_HOME="${CLO_HOME}")
message("CLO_HOME is set to ${CLO_HOME}")

add_executable(Launcher CLO3DLauncher.cpp)
set_target_properties(Launcher PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_OUTPUT_DIR})
target_link_libraries(Launcher PRIVATE Logger)

# ----- Build "Extensions.dll" -----------------------------------------------------------------------------------------
# Step 1: Reusable custom widgets
find_package(Qt5 REQUIRED)
add_subdirectory(widgets)

# Step 2: Prepare requested extensions
find_package(clo-sdk REQUIRED)
find_package(polyhook2 REQUIRED)

set(CLO3D_UI_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
set(CLO3D_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE CLO3D_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)
add_subdirectory(extensions)

# Step 3: Build CLO3DExtensions.dll
add_library(CLO3DExtensions SHARED resources/resources.qrc CLO3DExtensions.cpp ${CLO3D_SOURCES})
set_target_properties(CLO3DExtensions PROPERTIES AUTOUIC_SEARCH_PATHS "${CLO3D_UI_DIRS}")
set_target_properties(CLO3DExtensions PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLO3D_OUTPUT_DIR})
target_include_directories(CLO3DExtensions PRIVATE ${CLO3D_INCLUDE_DIRS})
target_compile_definitions(CLO3DExtensions PRIVATE
        EXTEND_WITH_AUTHENTICATOR=$<BOOL:${EXTEND_WITH_AUTHENTICATOR}>
        EXTEND_WITH_PATTERN_BUILDER=$<BOOL:${EXTEND_WITH_PATTERN_BUILDER}>
)
target_link_libraries(CLO3DExtensions PRIVATE
        Logger Widgets
        polyhook2::polyhook2 clo-sdk::clo-sdk
        Qt5::Core Qt5::CorePrivate Qt5::Concurrent Qt5::Xml Qt5::Designer)

add_custom_command(TARGET CLO3DExtensions POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CLO3DExtensions> $<TARGET_FILE_DIR:CLO3DExtensions>
        COMMAND_EXPAND_LISTS
)

add_custom_command(TARGET CLO3DExtensions POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:CLO3DExtensions> "${CLO_HOME}/CLO3DExtensions.dll"
        COMMENT "Deploying CLO3DExtensions.dll to CLO directory"
)

# ----- Build development tools ----------------------------------------------------------------------------------------

add_subdirectory(tools)

# ----- Build tests ----------------------------------------------------------------------------------------------------

add_subdirectory(test)

# ----------------------------------------------------------------------------------------------------------------------