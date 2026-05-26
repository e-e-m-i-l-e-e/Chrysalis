#ifndef FASHIONDESIGNAPPS_LOGGERREGISTRY_H
#define FASHIONDESIGNAPPS_LOGGERREGISTRY_H

#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "Logger.h"

class LoggerRegistry {
public:
    explicit LoggerRegistry();

    Logger& get(const char* name);
    const std::unordered_map<const char*, Logger>& getLoggers();

private:
    std::shared_ptr<spdlog::sinks::stdout_sink_mt> consoleSink_;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> commonFileSink_;

    std::unordered_map<const char*, Logger> loggers_;
};

#endif //FASHIONDESIGNAPPS_LOGGERREGISTRY_H