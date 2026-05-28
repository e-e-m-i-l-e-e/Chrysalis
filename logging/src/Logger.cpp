#include "Logger.h"

#include <spdlog/pattern_formatter.h>

#include "LoggerFormatter.h"
#include "formatters/NameFlagFormatter.h"
#include "formatters/LevelFlagFormatter.h"

Logger::Logger(const std::string& loggingDirectory, const char* name)
    : name_(name), logger_(spdlog::logger(name)),
      fileSink_(std::make_shared<spdlog::sinks::basic_file_sink_st>(loggingDirectory + "/" + name + ".log", true)) {
    LoggerFormatter<NameFlagFormatter, LevelFlagFormatter>::apply(fileSink_);
    addSink(fileSink_);
}

void Logger::flush() const {
    fileSink_->flush();
}

void Logger::addSink(const std::shared_ptr<spdlog::sinks::sink>& sink) {
    logger_.sinks().push_back(sink);
}

const char* Logger::getName() const {
    return name_;
}

spdlog::level::level_enum Logger::getLevel() const {
    return logger_.level();
}

void Logger::setLevel(const spdlog::level::level_enum level) {
    logger_.set_level(level);
}
