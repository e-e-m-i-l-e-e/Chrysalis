#include "LoggingToolSettings.h"

#include <QString>

#include "Logger.h"

void LoggingToolSettings::read() {
}

void LoggingToolSettings::write() {
}

std::pair<std::list<LoggingToolSettings::LoggerEntry>, std::list<QString>> LoggingToolSettings::getEntries() {
    std::list<LoggerEntry> entries;
    for (const auto logger: Logger::getAll()) {
        entries.push_back({QString(logger->name().c_str()), logger->level()});
    }
    return {entries, {"DEBUG", "TRACE", "INFO"}};
}
