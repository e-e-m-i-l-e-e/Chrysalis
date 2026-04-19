option(BYPASS_AUTH "Skip authentication with \"CLOSET\"" ON)
option(EXTEND_WITH_PATTERN_BUILDER "Add \"Pattern Builder Extension\"" ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ----- Build "Launcher.exe" -------------------------------------------------------------------------------------------

set(CLO_HOME "C:/Program Files/CLO Standalone OnlineAuth" CACHE STRING "Folder where CLO3D is installed")

add_compile_definitions(CLO_HOME="${CLO_HOME}")
message("CLO_HOME is set to ${CLO_HOME}")

add_executable(Launcher launcher.cpp)
target_link_libraries(Launcher PRIVATE Logger)

# ----- Build "Extensions.dll" -----------------------------------------------------------------------------------------
# Step 1: Reusable custom widgets
find_package(Qt5 REQUIRED)
add_subdirectory(widgets)

# Step 2: Prepare requested extensions
find_package(clo-sdk REQUIRED)
find_package(polyhook2 REQUIRED)

add_subdirectory(extensions)

file(GLOB_RECURSE CLO3D_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
file(GLOB_RECURSE CLO3D_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(CLO3DExtensions SHARED resources/resources.qrc extensions.cpp)
set_target_properties(CLO3DExtensions PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")
target_include_directories(CLO3DExtensions PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(CLO3DExtensions PRIVATE ${CLO3D_SOURCES})
target_link_libraries(CLO3DExtensions PRIVATE
        Logger Widgets polyhook2::polyhook2 clo-sdk::clo-sdk
        Qt5::Core Qt5::CorePrivate Qt5::Concurrent Qt5::Xml Qt5::Designer)

#set(CORE_SOURCES ${SRC} ${PATTERN_BUILDER_SRC} ${PATTERN_BUILDER_H}
#        include/ExtensionsSettings.h
#        include/MVDockingButton.h include/MVDockWidgetTitleBar.h include/MVDockWidgetTitleBarBase.h)
#
#find_package(clo-sdk REQUIRED)
#
#add_library(Core STATIC)
#target_sources(Core PRIVATE ${CORE_SOURCES})
#set_target_properties(Core PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui;${PATTERN_BUILDER_UI}")
#target_include_directories(Core PUBLIC include ${PATTERN_BUILDER_INCLUDE})
#target_link_libraries(Core PUBLIC Logger HooksManager clo-sdk::clo-sdk Qt5::Designer Qt5::Xml Qt5::Concurrent Qt5::Network Qt5::CorePrivate UI)
#
#add_library(Extensions SHARED resources/resources.qrc extensions.cpp)
#target_link_libraries(Extensions PRIVATE HooksManager Core)
#
#add_custom_command(TARGET Extensions POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_RUNTIME_DLLS:Extensions>
#        $<TARGET_FILE_DIR:Extensions>
#        COMMAND_EXPAND_LISTS
#)
#
#add_custom_command(TARGET Extensions POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:Extensions>
#        "${CLO_HOME}/Extensions.dll"
#        COMMENT "Deploying Extensions.dll to CLO directory"
#)


# ----- Build development tools ----------------------------------------------------------------------------------------

add_subdirectory(tools)

# ----- Build tests ----------------------------------------------------------------------------------------------------

add_subdirectory(test)

# ----------------------------------------------------------------------------------------------------------------------