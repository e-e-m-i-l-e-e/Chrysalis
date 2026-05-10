#ifndef FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H
#define FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H

#include "unordered_map"

#include "BaseExtensionSettings.h"

class LoggingToolSettings: public BaseExtensionSettings {
public:
    void read() override;
    void write() override;

    struct LoggerEntry {
        const QString name;
        const int level;
    };
    std::pair<std::list<LoggerEntry>, std::list<QString>> getEntries();
private:
    std::unordered_map<QString, int> logLevels_;
};

#endif //FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H