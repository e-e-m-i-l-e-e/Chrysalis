#include "LoggerRegistry.h"

#include <ranges>

#include "LoggerFormatter.h"
#include "formatters/ColoredNameFlagFormatter.h"
#include "formatters/ColoredLevelFlagFormatter.h"

LoggerRegistry::LoggerRegistry(const char* loggingDirectory, const char* fileName)
    : loggingDirectory_(loggingDirectory), fileName_(fileName),
      consoleSink_(std::make_shared<spdlog::sinks::stdout_sink_mt>()),
      commonFileSink_(std::make_shared<spdlog::sinks::basic_file_sink_mt>(loggingDirectory_ + "/" + fileName_ + ".log", true)) {
    LoggerFormatter<NameFlagFormatter, LevelFlagFormatter>::apply(commonFileSink_);
    LoggerFormatter<ColoredNameFlagFormatter, ColoredLevelFlagFormatter>::apply(consoleSink_);
}

LoggerRegistry::~LoggerRegistry() {
    for (const auto logger: loggers_) {
        delete logger;
    }
}

std::vector<Logger*>::const_iterator LoggerRegistry::begin() const {
    return loggers_.cbegin();
}

std::vector<Logger*>::const_iterator LoggerRegistry::end() const {
    return loggers_.cend();
}

size_t LoggerRegistry::size() const {
    return loggers_.size();
}

void LoggerRegistry::addListener(BaseLoggerRegistryListener* listener) {
    listeners_.push_front(listener);
}

const char* LoggerRegistry::getFileName() const {
    return fileName_;
}

std::string LoggerRegistry::getLoggingDirectory() const {
    return loggingDirectory_;
}

void LoggerRegistry::setFileName(const char* fileName)
{
}

void LoggerRegistry::setLoggingDirectory(std::string loggingDirectory)
{
}

Logger* LoggerRegistry::at(const int i) const {
    return loggers_[i];
}

Logger* LoggerRegistry::get(const char* name) {
    if (!loggersMap_.contains(name)) {
        const auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(loggingDirectory_ + "/" + name + ".log", true);
        LoggerFormatter<NameFlagFormatter, LevelFlagFormatter>::apply(fileSink);

        const auto logger = new Logger(name);
        logger->addSink(fileSink);
        logger->addSink(consoleSink_);
        logger->addSink(commonFileSink_);

        loggers_.push_back(logger);
        loggersMap_.emplace(name, logger);
        for (const auto listener: listeners_) {
            listener->loggerAdded(logger);
        }
    }
    return loggersMap_.at(name);
}
