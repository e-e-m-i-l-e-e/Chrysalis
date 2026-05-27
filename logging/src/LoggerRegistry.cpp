#include "LoggerRegistry.h"

#include <ranges>

#include "LoggerFormatter.h"
#include "formatters/ColoredNameFlagFormatter.h"
#include "formatters/ColoredLevelFlagFormatter.h"

LoggerRegistry::LoggerRegistry(const char* loggingDirectory, const char* fileName)
    : loggingDirectory_(loggingDirectory),
      consoleSink_(std::make_shared<spdlog::sinks::stdout_sink_mt>()),
      commonFileSink_(std::make_shared<spdlog::sinks::basic_file_sink_mt>(loggingDirectory_ + "/" + fileName + ".log")) {
    LoggerFormatter<NameFlagFormatter, LevelFlagFormatter>::apply(commonFileSink_);
    LoggerFormatter<ColoredNameFlagFormatter, ColoredLevelFlagFormatter>::apply(consoleSink_);
}

LoggerRegistry::~LoggerRegistry() {
    for (const auto logger: loggers_ | std::views::values) {
        delete logger;
    }
}

void LoggerRegistry::addListener(BaseLoggerRegistryListener* listener) {
    listeners_.push_front(listener);
}

void LoggerRegistry::setFileName(const char* fileName)
{
}

void LoggerRegistry::setLoggingDirectory(const char* loggingDirectory)
{
}

Logger* LoggerRegistry::get(const char* name) {
    if (!loggers_.contains(name)) {
        const auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(loggingDirectory_ + "/" + name + ".log");
        LoggerFormatter<NameFlagFormatter, LevelFlagFormatter>::apply(fileSink);

        const auto logger = new Logger(name);
        logger->addSink(fileSink);
        logger->addSink(consoleSink_);
        logger->addSink(commonFileSink_);

        loggers_.emplace(name, logger);
        for (const auto listener: listeners_) {
            listener->loggerAdded(logger);
        }
    }
    return loggers_.at(name);
}

const std::unordered_map<const char*, Logger*>& LoggerRegistry::getLoggers() const {
    return loggers_;
}
