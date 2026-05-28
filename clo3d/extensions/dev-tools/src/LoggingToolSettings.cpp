#include "LoggingToolSettings.h"

LoggingToolSettings::LoggingToolSettings(LoggerRegistry& registry): registry_(registry) {}

void LoggingToolSettings::read() {
}

void LoggingToolSettings::write() {
}

void LoggingToolSettings::flush() const {
    registry_.flush();
}

void LoggingToolSettings::flush(const int i) const {
    registry_.at(i)->flush();
}

QString LoggingToolSettings::getLoggingDirectory() const {
    return QString::fromStdString(registry_.getLoggingDirectory());
}

const char* LoggingToolSettings::getCommonFileName() const {
    return registry_.getFileName();
}

QString LoggingToolSettings::getLoggerFileLocation() const {
    return getLoggerFileLocation(getCommonFileName());
}

QString LoggingToolSettings::getLoggerFileLocation(const QString& loggerName) const {
    return getLoggingDirectory().append("/").append(loggerName).append(".log");
}
