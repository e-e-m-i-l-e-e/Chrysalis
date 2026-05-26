#include "Logging.h"

#include <spdlog/pattern_formatter.h>

Logger::Logger(const char* name): name_(name), logger_(spdlog::logger(name)) {}

void Logger::addSink(const std::shared_ptr<spdlog::sinks::sink>& sink) {
    logger_.sinks().push_back(sink);
}

const char* Logger::getName() const {
    return name_;
}
