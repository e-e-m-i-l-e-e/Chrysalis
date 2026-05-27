#include "LoggingToolSettings.h"

LoggingToolSettings::LoggingToolSettings(LoggerRegistry& registry): registry_(registry) {}

void LoggingToolSettings::read() {
}

void LoggingToolSettings::write() {
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
