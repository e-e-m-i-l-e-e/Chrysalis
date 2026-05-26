#include "LoggerRegistry.h"

#include "windows.h"

#include "../private/NameFlagFormatter.h"
#include "LevelFlagFormatter.h"
#include "../private/ColoredNameFlagFormatter.h"
#include "../private/ColoredLevelFlagFormatter.h"

template<typename NameFlag, typename LevelFlag>
static void format(const std::shared_ptr<spdlog::sinks::sink> sync) {
    static constexpr auto PATTERN = "%Y-%m-%d %H:%M:%S.%e [%*] [%&] %v";
    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<NameFlag>('&');
    formatter->add_flag<LevelFlag>('*');
    formatter->set_pattern(PATTERN);
    sync->set_formatter(std::move(formatter));
}

LoggerRegistry::LoggerRegistry(): consoleSink_(std::make_shared<spdlog::sinks::stdout_sink_mt>()),
                                  commonFileSink_(std::make_shared<spdlog::sinks::basic_file_sink_mt>("test.log")) {
    const bool attached = AttachConsole(ATTACH_PARENT_PROCESS);
    if (const bool allocated = !attached && AllocConsole(); attached || allocated)
    {
        FILE* f = nullptr;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONOUT$", "w", stderr);
    }

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    auto enableVT = [](const DWORD stdHandle)
    {
        const HANDLE h = GetStdHandle(stdHandle);
        if (h == INVALID_HANDLE_VALUE) return;
        DWORD mode = 0;
        if (GetConsoleMode(h, &mode)) SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    };
    enableVT(STD_OUTPUT_HANDLE);
    enableVT(STD_ERROR_HANDLE);

    format<NameFlagFormatter, LevelFlagFormatter>(commonFileSink_);
    format<ColoredNameFlagFormatter, ColoredLevelFlagFormatter>(consoleSink_);
}

Logger& LoggerRegistry::get(const char* name) {
    if (!loggers_.contains(name)) {
        const auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string(name) + ".log");
        format<NameFlagFormatter, LevelFlagFormatter>(fileSink);

        Logger logger(name);
        logger.addSink(fileSink);
        logger.addSink(consoleSink_);
        logger.addSink(commonFileSink_);

        loggers_.emplace(name, logger);
    }
    return loggers_.at(name);
}

const std::unordered_map<const char*, Logger>& LoggerRegistry::getLoggers() {
    return loggers_;
}
