#ifndef CHRYSALIS_LOGGING_H
#define CHRYSALIS_LOGGING_H

#include "LoggerRegistry.h"

namespace Logging {
    inline LoggerRegistry REGISTRY(LOGS_DIR, LOGS_FILE_NAME);

    namespace Message {
        static constexpr auto LOG_SAVING_FILE = FMT_STRING("Saving file: {}.");
        static constexpr auto LOG_FAILED_TO_OPEN_FILE = FMT_STRING("Failed to open file: {}.");
        static constexpr auto LOG_FAILED_TO_SAVE_FILE = FMT_STRING("Failed to save file: {}.");
        static constexpr auto LOG_FAILED_TO_CREATE_PATH = FMT_STRING("Failed to create path: {}.");
        static constexpr auto LOG_FOLDER_WAS_CREATED_IN_DIRECTORY = FMT_STRING("Folder \"{}\" was created in \"{}\" directory.");
    }
}

#define LOGGER Logging::REGISTRY.get(LOGGER_NAME)
#define LOGGER_NAMED(name) Logging::REGISTRY.get(name)

#define LOG_TRACE(...) LOGGER->trace(__VA_ARGS__)
#define LOG_DEBUG(...) LOGGER->debug(__VA_ARGS__)
#define LOG_INFO(...) LOGGER->info(__VA_ARGS__)
#define LOG_WARN(...) LOGGER->warn(__VA_ARGS__)
#define LOG_ERROR(...) LOGGER->error(__VA_ARGS__)
#define LOG_CRITICAL(...) LOGGER->critical(__VA_ARGS__)

#define LOG_TO(name, level, ...) LOGGER_NAMED(name)->log(level, __VA_ARGS__)
#define LOG_TRACE_TO(name, ...) LOGGER_NAMED(name)->trace(__VA_ARGS__)
#define LOG_DEBUG_TO(name, ...) LOGGER_NAMED(name)->debug(__VA_ARGS__)
#define LOG_INFO_TO(name, ...) LOGGER_NAMED(name)->info(__VA_ARGS__)
#define LOG_WARN_TO(name, ...) LOGGER_NAMED(name)->warn(__VA_ARGS__)
#define LOG_ERROR_TO(name, ...) LOGGER_NAMED(name)->error(__VA_ARGS__)
#define LOG_CRITICAL_TO(name, ...) LOGGER_NAMED(name)->critical(__VA_ARGS__)

#endif //CHRYSALIS_LOGGING_H