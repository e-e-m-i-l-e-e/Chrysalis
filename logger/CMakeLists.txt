find_package(spdlog REQUIRED)

add_executable(NEWLOGGER main.cpp
        src/Logger.cpp
        src/LoggerRegistry.cpp
        src/LevelFlagFormatter.cpp
        src/ColoredLevelFlagFormatter.cpp
        src/NameFlagFormatter.cpp
        src/ColoredNameFlagFormatter.cpp
)
target_include_directories(NEWLOGGER PUBLIC include)
target_include_directories(NEWLOGGER PRIVATE private)
target_link_libraries(NEWLOGGER PRIVATE spdlog::spdlog)