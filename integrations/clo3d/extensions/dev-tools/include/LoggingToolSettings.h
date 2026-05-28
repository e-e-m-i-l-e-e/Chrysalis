#ifndef FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H
#define FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H

#include "BaseExtensionSettings.h"
#include "LoggerRegistry.h"

class LoggingToolSettings: public BaseExtensionSettings {
    struct Keys {
        static constexpr auto LOGGING_DIRECTORY = "loggingDirectory";
        static constexpr auto LOGGER_FILE_NAME = "fileName";
        static constexpr auto LOGGER_LOG_LEVEL = "logLevel";
    };
    struct Defaults {
        static constexpr auto LOGGING_DIRECTORY = LOGS_DIR;
        static constexpr auto LOGGER_FILE_NAME = LOGS_FILE_NAME;
        static constexpr auto LOGGER_LOG_LEVEL = spdlog::level::info;
    };
public:
    explicit LoggingToolSettings(LoggerRegistry& registry);

    void read() override;
    void write() override;

    void flush() const;
    void flush(int i) const;

    void read(int loggerIndex, const Logger* logger) const;

    const std::string& getFileName() const;
    int getLogLevel(int loggerIndex) const;
    QString getLoggingDirectory() const;

    void setFileName(const QString& fileName) const;
    void setLogLevel(int loggerIndex, int logLevel) const;
    void setLoggingDirectory(const QString& loggingDirectory) const;

    QString getLoggerFileLocation() const;
    QString getLoggerFileLocation(const QString& loggerName) const;
private:
    void readLoggerSettings(int loggerIndex, const Logger* logger) const;

    LoggerRegistry& registry_;
};

#endif //FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H