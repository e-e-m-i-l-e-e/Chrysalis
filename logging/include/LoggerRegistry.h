#ifndef CHRYSALIS_LOGGERREGISTRY_H
#define CHRYSALIS_LOGGERREGISTRY_H

#include <map>
#include <cstddef>
#include <forward_list>

#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "Logger.h"
#include "BaseConsoleUser.h"
#include "LoggingLibraryExport.h"
#include "BaseLoggerRegistryListener.h"

namespace Logging {
    class LOGGING LoggerRegistry: BaseConsoleUser {
        friend class BaseLoggerRegistryListener;
    public:
        explicit LoggerRegistry(const char* loggingDirectory, const char* fileName);
        ~LoggerRegistry();

        [[nodiscard]] std::vector<Logger*>::const_iterator begin() const;
        [[nodiscard]] std::vector<Logger*>::const_iterator end() const;

        [[nodiscard]] size_t size() const;

        [[nodiscard]] Logger* at(int i) const;
        [[nodiscard]] Logger* get(const char* name);

        void flush() const;

        [[nodiscard]] const std::string& getFileName() const;
        [[nodiscard]] const std::string& getLoggingDirectory() const;

        void setFileName(const std::string& fileName);
        void setLoggingDirectory(const std::string& loggingDirectory);
    private:
        void addListener(BaseLoggerRegistryListener* listener);

        std::string fileName_;
        std::string loggingDirectory_;

        std::vector<Logger*> loggers_;
        std::map<const char*, Logger*> loggersMap_;
        std::forward_list<BaseLoggerRegistryListener*> listeners_;

        std::shared_ptr<spdlog::sinks::stdout_sink_mt> consoleSink_;
        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> commonFileSink_;
    };
}

#endif //CHRYSALIS_LOGGERREGISTRY_H