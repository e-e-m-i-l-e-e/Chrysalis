#include "Logger.h"

#include <string>
#include <memory>

#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/sink.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/sinks/basic_file_sink.h>

Logger::Logger(const std::string& loggingDirectory, const char* name)
    : name_(name), logger_(spdlog::logger(name)),
      fileSink_(createFileSink<spdlog::details::null_mutex>(loggingDirectory, name)) {
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

void Logger::setLoggingDirectory(const std::string& loggingDirectory) {
    fileSink_ = createFileSink<spdlog::details::null_mutex>(loggingDirectory, logger_.name().c_str());
    logger_.sinks()[2] = fileSink_;
}

void Logger::setCommonFileSink(const std::shared_ptr<spdlog::sinks::basic_file_sink_mt>& sink) {
    logger_.sinks()[1] = sink;
}
