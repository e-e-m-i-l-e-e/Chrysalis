find_package(polyhook2 REQUIRED)

add_library(HooksLibrary INTERFACE)
target_include_directories(HooksLibrary INTERFACE include)
target_link_libraries(HooksLibrary INTERFACE polyhook2::polyhook2)