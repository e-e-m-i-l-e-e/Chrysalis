#include "LoggerRegistry.h"

#include <ranges>

#include "formatters/ColoredNameFlagFormatter.h"
#include "formatters/ColoredLevelFlagFormatter.h"

LoggerRegistry::LoggerRegistry(const char* loggingDirectory, const char* fileName)
    : loggingDirectory_(loggingDirectory),
      consoleSink_(std::make_shared<spdlog::sinks::stdout_sink_mt>()),
      commonFileSink_(std::make_shared<spdlog::sinks::basic_file_sink_mt>(loggingDirectory_ + "/" + fileName + ".log")) {
    fileFormatter_.apply(commonFileSink_);
    consoleFormatter_.apply(consoleSink_);
}

LoggerRegistry::~LoggerRegistry() {
    for (const auto logger: loggers_ | std::views::values) {
        delete logger;
    }
}

Logger* LoggerRegistry::get(const char* name) {
    if (!loggers_.contains(name)) {
        const auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(loggingDirectory_ + "/" + name + ".log");
        fileFormatter_.apply(fileSink);

        const auto logger = new Logger(name);
        logger->addSink(fileSink);
        logger->addSink(consoleSink_);
        logger->addSink(commonFileSink_);

        loggers_.emplace(name, logger);
    }
    return loggers_.at(name);
}

const std::unordered_map<const char*, Logger*>& LoggerRegistry::getLoggers() {
    return loggers_;
}
