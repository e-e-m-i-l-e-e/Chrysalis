#include "LoggerRegistry.h"

#include <mutex>
#include <memory>
#include <vector>
#include <cstddef>

#include <spdlog/sinks/stdout_sinks.h>

#include "Logger.h"
#include "LoggerFormatter.h"
#include "BaseLoggerRegistryListener.h"
#include "formatters/NameFlagFormatter.h"
#include "formatters/LevelFlagFormatter.h"
#include "formatters/ColoredNameFlagFormatter.h"
#include "formatters/ColoredLevelFlagFormatter.h"

using namespace Logging;

LoggerRegistry::LoggerRegistry(const char* loggingDirectory, const char* fileName)
    : fileName_(fileName), loggingDirectory_(loggingDirectory),
      consoleSink_(std::make_shared<spdlog::sinks::stdout_sink_mt>()),
      commonFileSink_(Logger::createFileSink<std::mutex>(loggingDirectory_, fileName_)) {
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

void LoggerRegistry::flush() const {
    commonFileSink_->flush();
}

void LoggerRegistry::addListener(BaseLoggerRegistryListener* listener) {
    listeners_.push_front(listener);
}

const std::string& LoggerRegistry::getFileName() const {
    return fileName_;
}

const std::string& LoggerRegistry::getLoggingDirectory() const {
    return loggingDirectory_;
}

void LoggerRegistry::setFileName(const std::string& fileName) {
    if (fileName_ == fileName) return;
    fileName_ = fileName;
    commonFileSink_ = Logger::createFileSink<std::mutex>(loggingDirectory_, fileName_);
    for (const auto& logger: loggers_) {
        logger->setCommonFileSink(commonFileSink_);
    }
}

void LoggerRegistry::setLoggingDirectory(const std::string& loggingDirectory) {
    if (loggingDirectory_ == loggingDirectory) return;
    loggingDirectory_ = loggingDirectory;
    commonFileSink_ = Logger::createFileSink<std::mutex>(loggingDirectory_, fileName_);
    for (const auto& logger: loggers_) {
        logger->setCommonFileSink(commonFileSink_);
        logger->setLoggingDirectory(loggingDirectory_);
    }
}

Logger* LoggerRegistry::at(const int i) const {
    return loggers_[i];
}

Logger* LoggerRegistry::get(const char* name) {
    if (!loggersMap_.contains(name)) {
        const auto logger = new Logger(loggingDirectory_, name);
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
