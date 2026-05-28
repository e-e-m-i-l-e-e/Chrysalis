#ifndef CHRYSALIS_LOGGER_H
#define CHRYSALIS_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "LoggerFormatter.h"
#include "formatters/NameFlagFormatter.h"
#include "formatters/LevelFlagFormatter.h"

class Logger {
    friend class LoggerRegistry;

    explicit Logger(const std::string& loggingDirectory, const char* name);
public:
    constexpr static short LOGGER_NAME_LENGTH = 20;

    const char* getName() const;

    spdlog::level::level_enum getLevel() const;
    void setLevel(spdlog::level::level_enum level);

    void flush() const;
    void addSink(const std::shared_ptr<spdlog::sinks::sink>& sink);

    template<typename... Args>
    void log(spdlog::level::level_enum lvl, spdlog::format_string_t<Args...> fmt, Args &&... args) {
        logger_.log(lvl, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
        exit(1);
    }

private:
    template<typename Mutex>
    static std::shared_ptr<spdlog::sinks::basic_file_sink<Mutex>> createFileSink(const std::string& loggingDirectory, const std::string& name) {
        const auto sink = std::make_shared<spdlog::sinks::basic_file_sink<Mutex>>(loggingDirectory + "/" + name + ".log", true);
        LoggerFormatter<NameFlagFormatter, LevelFlagFormatter>::apply(sink);
        return sink;
    }

    void setLoggingDirectory(const std::string& loggingDirectory);
    void setCommonFileSink(const std::shared_ptr<spdlog::sinks::basic_file_sink_mt>& sink);

    const char* name_;

    spdlog::logger logger_;
    std::shared_ptr<spdlog::sinks::basic_file_sink_st> fileSink_;
};

#endif //CHRYSALIS_LOGGER_H