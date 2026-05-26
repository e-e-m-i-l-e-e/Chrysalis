#ifndef FASHIONDESIGNAPPS_LOGGERREGISTRY_H
#define FASHIONDESIGNAPPS_LOGGERREGISTRY_H

#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "Logger.h"
#include "LoggerFormatter.h"
#include "BaseConsoleUser.h"

class NameFlagFormatter;
class LevelFlagFormatter;
class ColoredNameFlagFormatter;
class ColoredLevelFlagFormatter;

class LoggerRegistry: BaseConsoleUser {
public:
    explicit LoggerRegistry(const char* loggingDirectory, const char* fileName);
    ~LoggerRegistry();

    Logger* get(const char* name);
    const std::unordered_map<const char*, Logger*>& getLoggers();

private:
    std::string loggingDirectory_;
    std::unordered_map<const char*, Logger*> loggers_;

    LoggerFormatter<NameFlagFormatter, LevelFlagFormatter> fileFormatter_;
    LoggerFormatter<ColoredNameFlagFormatter, ColoredLevelFlagFormatter> consoleFormatter_;

    std::shared_ptr<spdlog::sinks::stdout_sink_mt> consoleSink_;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> commonFileSink_;
};

#endif //FASHIONDESIGNAPPS_LOGGERREGISTRY_H