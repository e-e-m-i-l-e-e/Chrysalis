#ifndef FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H
#define FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H

#include "BaseExtensionSettings.h"
#include "LoggerRegistry.h"

class LoggingToolSettings: public BaseExtensionSettings {
public:
    explicit LoggingToolSettings(LoggerRegistry& registry);

    void read() override;
    void write() override;

    void flush() const;
    void flush(int i) const;

    QString getLoggingDirectory() const;
    const char* getCommonFileName() const;
    QString getLoggerFileLocation() const;
    QString getLoggerFileLocation(const QString& loggerName) const;
private:
    LoggerRegistry& registry_;
};

#endif //FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H