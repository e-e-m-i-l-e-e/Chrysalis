#ifndef FASHIONDESIGNAPPS_LOGGER_H
#define FASHIONDESIGNAPPS_LOGGER_H

#include <spdlog/spdlog.h>

class Logger {
    friend class LoggerRegistry;

    explicit Logger(const char* name);
public:
    constexpr static short LOGGER_NAME_LENGTH = 20;

    const char* getName() const;

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
    template<typename... Args>
    void log(spdlog::level::level_enum lvl, spdlog::format_string_t<Args...> fmt, Args &&... args) {
        logger_.log(lvl, fmt, std::forward<Args>(args)...);
    }

    void addSink(const std::shared_ptr<spdlog::sinks::sink>& sink);

    const char* name_;

    spdlog::logger logger_;
    spdlog::level::level_enum level_ = spdlog::level::trace;
};

#endif //FASHIONDESIGNAPPS_LOGGER_H