#include "LoggingToolSettings.h"

#include "Logging.h"
#define LOGGER_NAME "Logging Tool Settings"

LoggingToolSettings::LoggingToolSettings(LoggerRegistry& registry): registry_(registry) {}

void LoggingToolSettings::read() {
    setFileName(settings_->value(Keys::LOGGER_FILE_NAME, Defaults::LOGGER_FILE_NAME).toString());
    setLoggingDirectory(settings_->value(Keys::LOGGING_DIRECTORY, Defaults::LOGGING_DIRECTORY).toString());

    int i = 0;
    for (const auto& logger: registry_) {
        readLoggerSettings(i++, logger);
    }
}

void LoggingToolSettings::write() {
    settings_->setValue(Keys::LOGGER_FILE_NAME, getFileName());
    settings_->setValue(Keys::LOGGING_DIRECTORY, getLoggingDirectory());

    int i = 0;
    for (const auto& logger: registry_) {
        settings_->beginGroup(logger->getName());
        settings_->setValue(Keys::LOGGER_LOG_LEVEL, getLogLevel(i++));
        settings_->endGroup();
    }
}

void LoggingToolSettings::flush() const {
    registry_.flush();
}

void LoggingToolSettings::flush(const int i) const {
    registry_.at(i)->flush();
}

void LoggingToolSettings::read(const int loggerIndex, const Logger* logger) const {
    settings_->beginGroup(typeid(*this).name() + 6);
    readLoggerSettings(loggerIndex, logger);
    settings_->endGroup();
}

void LoggingToolSettings::readLoggerSettings(const int loggerIndex, const Logger* logger) const {
    LOG_DEBUG("Applying settings to \"{}\" logger.", logger->getName());
    settings_->beginGroup(logger->getName());
    setLogLevel(loggerIndex, settings_->value(Keys::LOGGER_LOG_LEVEL, Defaults::LOGGER_LOG_LEVEL).toInt());
    settings_->endGroup();
}

int LoggingToolSettings::getLogLevel(const int loggerIndex) const {
    return registry_.at(loggerIndex)->getLevel();
}

QString LoggingToolSettings::getLoggingDirectory() const {
    return QString::fromStdString(registry_.getLoggingDirectory());
}

const char* LoggingToolSettings::getFileName() const {
    return registry_.getFileName();
}

void LoggingToolSettings::setLogLevel(const int loggerIndex, int logLevel) const {
    registry_.at(loggerIndex)->setLevel(static_cast<spdlog::level::level_enum>(logLevel));
}

void LoggingToolSettings::setFileName(const QString& fileName) const {
    registry_.setFileName(fileName.toUtf8().data());
}

void LoggingToolSettings::setLoggingDirectory(const QString& loggingDirectory) const {
    registry_.setLoggingDirectory(loggingDirectory.toStdString());
}

QString LoggingToolSettings::getLoggerFileLocation() const {
    return getLoggerFileLocation(getFileName());
}

QString LoggingToolSettings::getLoggerFileLocation(const QString& loggerName) const {
    return getLoggingDirectory().append("/").append(loggerName).append(".log");
}
