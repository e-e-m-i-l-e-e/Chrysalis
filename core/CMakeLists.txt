file(GLOB_RECURSE SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(Core STATIC ${SRC} include/ExtensionsSettings.h)
set_target_properties(Core PROPERTIES AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
target_include_directories(Core PUBLIC include)
target_link_libraries(Core PUBLIC Logger HooksManager CloUI Qt5::Designer Qt5::Xml Qt5::Concurrent)