#ifndef FASHIONDESIGNAPPS_LOGGERREGISTRY_H
#define FASHIONDESIGNAPPS_LOGGERREGISTRY_H

#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "Logger.h"
#include "BaseConsoleUser.h"
#include "BaseLoggerRegistryListener.h"

class LoggerRegistry: BaseConsoleUser {
    friend class BaseLoggerRegistryListener;
public:
    explicit LoggerRegistry(const char* loggingDirectory, const char* fileName);
    ~LoggerRegistry();

    Logger* get(const char* name);
    [[nodiscard]] const std::unordered_map<const char*, Logger*>& getLoggers() const;

    const char* getFileName() const;
    std::string getLoggingDirectory() const;

    void setFileName(const char* fileName);
    void setLoggingDirectory(std::string loggingDirectory);
private:

    void addListener(BaseLoggerRegistryListener* listener);

    const char* fileName_;
    std::string loggingDirectory_;
    std::unordered_map<const char*, Logger*> loggers_;
    std::forward_list<BaseLoggerRegistryListener*> listeners_;

    std::shared_ptr<spdlog::sinks::stdout_sink_mt> consoleSink_;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> commonFileSink_;
};

#endif //FASHIONDESIGNAPPS_LOGGERREGISTRY_H