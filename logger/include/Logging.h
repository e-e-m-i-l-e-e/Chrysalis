#ifndef FASHIONDESIGNAPPS_LOGGING_H
#define FASHIONDESIGNAPPS_LOGGING_H

#include "LoggerRegistry.h"

namespace Logging {
    inline LoggerRegistry registry;
}

#define LOGGER Logging::registry.get(LOGGER_NAME)
#define LOGGER_NAMED(name) Logging::registry.get(name)

#define LOG_TRACE(...) LOGGER.trace(__VA_ARGS__)
#define LOG_DEBUG(...) LOGGER.debug(__VA_ARGS__)
#define LOG_INFO(...) LOGGER.info(__VA_ARGS__)
#define LOG_WARN(...) LOGGER.warn(__VA_ARGS__)
#define LOG_ERROR(...) LOGGER.error(__VA_ARGS__)
#define LOG_CRITICAL(...) LOGGER.critical(__VA_ARGS__)

#define LOG_TRACE_TO(name, ...) LOGGER_NAMED(name).trace(__VA_ARGS__)
#define LOG_DEBUG_TO(name, ...) LOGGER_NAMED(name).debug(__VA_ARGS__)
#define LOG_INFO_TO(name, ...) LOGGER_NAMED(name).info(__VA_ARGS__)
#define LOG_WARN_TO(name, ...) LOGGER_NAMED(name).warn(__VA_ARGS__)
#define LOG_ERROR_TO(name, ...) LOGGER_NAMED(name).error(__VA_ARGS__)
#define LOG_CRITICAL_TO(name, ...) LOGGER_NAMED(name).critical(__VA_ARGS__)

#endif //FASHIONDESIGNAPPS_LOGGING_H