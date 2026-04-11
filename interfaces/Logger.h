#ifndef CLOEXTENSIONS_LOGGER_H
#define CLOEXTENSIONS_LOGGER_H

#include <ranges>
#include <filesystem>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/pattern_formatter.h>

// ─── Qt — optional ────────────────────────────────────────────────────────────
// The only Qt-specific code is the Qt message handler (installQtMessageHandler).
// All singleton/mutex/path logic uses std types unconditionally.
#ifdef QT_CORE_LIB
#   include <QDebug>
#   include <QFile>
#   include <QTextStream>
#   include <QDateTime>
#endif

// ─── Windows console attachment ───────────────────────────────────────────────
#ifdef _WIN32
#   include <Windows.h>
#endif

// LOGS_DIR must be defined via CMake
#ifndef LOGS_DIR
#   error "LOGS_DIR is not defined."
#endif

// =============================================================================
//  logger_detail — ANSI helpers and custom spdlog flag formatters
//
//  Coloring is surgical — only two tokens are colored per line:
//    [LEVEL] ← severity color  (fixed per level)
//    [NAME]  ← name color      (deterministic hash, never overlaps level palette)
//    message ← plain
// =============================================================================
namespace logger_detail {
    inline auto RESET = "\033[0m";

    // ── Fixed width for the logger name column ────────────────────────────────────
    // All name tokens are padded/truncated to this width so columns stay aligned
    // regardless of how long the logger name is.
    // Override before including this header if your names are longer.
#ifndef LOGGER_NAME_WIDTH
#   define LOGGER_NAME_WIDTH 19
#endif
    static constexpr std::size_t NAME_WIDTH = LOGGER_NAME_WIDTH;

    // Center-justify `s` to exactly NAME_WIDTH chars (pad with spaces or truncate).
    inline std::string namePadded(const std::string &s) {
        if (s.size() >= NAME_WIDTH) return s.substr(0, NAME_WIDTH);

        const std::size_t totalPad = NAME_WIDTH - s.size();
        const std::size_t rightPad  = totalPad / 2;
        const std::size_t leftPad = totalPad - rightPad;

        return std::string(leftPad, ' ') + s + std::string(rightPad, ' ');
    }

    // ── Level → ANSI color ────────────────────────────────────────────────────────
    inline const char *levelAnsi(spdlog::level::level_enum lvl) noexcept {
        switch (lvl) {
            case spdlog::level::trace: return "\033[90m"; // dark gray
            case spdlog::level::debug: return "\033[36m"; // cyan
            case spdlog::level::info: return "\033[32m"; // green
            case spdlog::level::warn: return "\033[33m"; // yellow
            case spdlog::level::err: return "\033[31m"; // red
            case spdlog::level::critical: return "\033[1;35m"; // bold magenta
            default: return "\033[0m";
        }
    }

    // ── Name → ANSI color ────────────────────────────────────────────────────────
    // Eight colors that do not visually overlap with any level color above.
    // The index is derived from a hash of the name so it is stable across runs.
    inline const char *nameAnsi(const std::string &name) noexcept {
        static constexpr const char *palette[] = {
            "\033[34m", // blue
            "\033[94m", // bright blue
            "\033[96m", // bright cyan
            "\033[92m", // bright green
            "\033[95m", // bright magenta
            "\033[93m", // bright yellow
            "\033[91m", // bright red
            "\033[97m", // bright white
        };
        constexpr std::size_t N = std::size(palette);
        return palette[std::hash<std::string>{}(name) % N];
    }

    // ── Uppercase level string, padded to 5 chars ─────────────────────────────────
    inline std::string levelUpper(const spdlog::level::level_enum lvl) {
        const auto sv = spdlog::level::to_string_view(lvl);
        std::string s(sv.begin(), sv.end());
        std::ranges::transform(s, s.begin(),
                               [](const unsigned char c) { return std::toupper(c); });
        if (s.size() < 5) s.append(5 - s.size(), ' ');
        return s;
    }

    // =============================================================================
    //  Custom spdlog flags registered under %* and %&
    //
    //  %*  →  LEVEL (uppercase, 5-chars)   — colored on console, plain in file
    //  %&  →  logger name                  — colored on console, plain in file
    // =============================================================================

    // ─── %* ──────────────────────────────────────────────────────────────────────
    struct ColoredLevelFlag : spdlog::custom_flag_formatter {
        void format(const spdlog::details::log_msg &msg,
                    const std::tm &,
                    spdlog::memory_buf_t &dest) override {
            const std::string out =
                    std::string(levelAnsi(msg.level)) + levelUpper(msg.level) + RESET;
            dest.append(out.data(), out.data() + out.size());
        }

        std::unique_ptr<custom_flag_formatter> clone() const override {
            return std::make_unique<ColoredLevelFlag>();
        }
    };

    struct PlainLevelFlag : spdlog::custom_flag_formatter {
        void format(const spdlog::details::log_msg &msg,
                    const std::tm &,
                    spdlog::memory_buf_t &dest) override {
            const std::string s = levelUpper(msg.level);
            dest.append(s.data(), s.data() + s.size());
        }

        std::unique_ptr<custom_flag_formatter> clone() const override {
            return std::make_unique<PlainLevelFlag>();
        }
    };

    // ─── %& ──────────────────────────────────────────────────────────────────────
    struct ColoredNameFlag : spdlog::custom_flag_formatter {
        void format(const spdlog::details::log_msg &msg,
                    const std::tm &,
                    spdlog::memory_buf_t &dest) override {
            const std::string name(msg.logger_name.begin(), msg.logger_name.end());
            const std::string out = std::string(nameAnsi(name)) + namePadded(name) + RESET;
            dest.append(out.data(), out.data() + out.size());
        }

        std::unique_ptr<custom_flag_formatter> clone() const override {
            return std::make_unique<ColoredNameFlag>();
        }
    };

    struct PlainNameFlag : spdlog::custom_flag_formatter {
        void format(const spdlog::details::log_msg &msg,
                    const std::tm &,
                    spdlog::memory_buf_t &dest) override {
            const std::string name(msg.logger_name.begin(), msg.logger_name.end());
            const std::string out = namePadded(name);
            dest.append(out.data(), out.data() + out.size());
        }

        std::unique_ptr<custom_flag_formatter> clone() const override {
            return std::make_unique<PlainNameFlag>();
        }
    };

    // ── Build a pattern_formatter with both custom flags registered ───────────────
    // Final line: 2026-03-06 11:33:11.766 [INFO ] [APP] message text
    static constexpr auto LOG_PATTERN = "%Y-%m-%d %H:%M:%S.%e [%*] [%&] %v";

    template<typename LevelFlag, typename NameFlag>
    std::unique_ptr<spdlog::pattern_formatter> makeFormatter() {
        auto f = std::make_unique<spdlog::pattern_formatter>(
            spdlog::pattern_time_type::local, spdlog::details::os::default_eol);
        f->add_flag<LevelFlag>('*');
        f->add_flag<NameFlag>('&');
        f->set_pattern(LOG_PATTERN);
        return f;
    }
} // namespace logger_detail


// =============================================================================
//  Logger — one singleton instance per named logger
// =============================================================================
class Logger {
public:
    Logger(const Logger &) = delete;

    Logger &operator=(const Logger &) = delete;

    // ── Factory ───────────────────────────────────────────────────────────────
    // name : identifier shown in every log line and used as the log file base name
    //        expands to  LOGS_DIR/<name>.log
    static Logger &getInstance(const std::string &name = "CLO") {

        if (name.length() > logger_detail::NAME_WIDTH) getInstance().warn("Logger name \"{}\" is too long.", name);

        auto &[mutex, instances] = registry();
        std::lock_guard lock(mutex);

        if (const auto it = instances.find(name); it != instances.end()) return *it->second;

        // Ensure the log directory exists before any file sink tries to open it.
        // This runs once per process — subsequent calls find the directory already there.
        const std::string logsDir = LOGS_DIR;
        std::filesystem::create_directories(logsDir);

#ifdef QT_CORE_LIB
        if (instances.empty()) installQtMessageHandler();
#endif

        // ── Shared "all.log" sink ─────────────────────────────────────────────
        // Created exactly once as a static local inside getInstance — NOT as an
        // inline function — so there is only ever one instance per process even
        // when both main.exe and a DLL include this header.
        // Every logger adds this sink so all messages are written to all.log in
        // addition to their own per-logger file.
        static const spdlog::sink_ptr allSink = [&logsDir] {
            auto s = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                logsDir + "/all.log", /*truncate=*/true);
            s->set_formatter(
                logger_detail::makeFormatter<
                    logger_detail::PlainLevelFlag,
                    logger_detail::PlainNameFlag>());
            s->set_level(spdlog::level::trace);
            return s;
        }();

        const std::string filePath = logsDir + "/" + name + ".log";
        auto inst = std::shared_ptr<Logger>(new Logger(name, filePath, allSink));
        instances.emplace(name, inst);
        return *inst;
    }

    // ── Logging methods ───────────────────────────────────────────────────────
    template<typename... Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args &&... args) const {
        log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&... args) const {
        log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&... args) const {
        log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&... args) const {
        log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&... args) const {
        log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args &&... args) const {
        log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
        exit(1);
    }

    // ── Accessors ─────────────────────────────────────────────────────────────
    const std::string &name() const {
        return name_;
    }
    const std::string &filePath() const {
        return filePath_;
    }
    spdlog::level::level_enum level() const {
        return logger_ ? logger_->level() : spdlog::level::off;
    }

    // ── Runtime level control ─────────────────────────────────────────────────
    void setLevel(const spdlog::level::level_enum level) const {
        if (logger_) logger_->set_level(level);
    }

    // ── Registry inspection ───────────────────────────────────────────────────
    // Returns a raw pointer to every Logger created in this process.
    // Pointers are stable — instances are owned by the registry shared_ptrs
    // which live for the lifetime of the process.
    // Thread-safe; locks the same mutex used by getInstance().
    static std::vector<Logger *> getAll() {
        auto &[mutex, instances] = registry();
        std::lock_guard lock(mutex);

        std::vector<Logger*> result;
        result.reserve(instances.size());
        for (const auto &inst: instances | std::views::values)
            result.push_back(inst.get());
        return result;
    }

private:
    // ── Shared registry ───────────────────────────────────────────────────────
    // Both getInstance() and getAll() access the same mutex + map through here,
    // so the static locals are guaranteed to be the same object in every call.
    struct RegistryData {
        std::mutex mutex;
        std::unordered_map<std::string, std::shared_ptr<Logger> > instances;
    };

    static RegistryData &registry() {
        static RegistryData s_data;
        return s_data;
    }

    // ── Constructor ───────────────────────────────────────────────────────────
    explicit Logger(const std::string &name,
                    const std::string &filePath,
                    const spdlog::sink_ptr &allSink)
        : name_(name), filePath_(filePath) {
        try {
            openWindowsConsole();

            // ── Reuse an already-registered logger if one exists ──────────────
            // Both the launcher EXE and the injected DLL share the same spdlog
            // registry (one global instance per process via the compiled lib).
            // If the DLL already registered this name, retrieve it directly
            // instead of constructing a duplicate — register_logger throws on
            // a duplicate name, and that exception can silently cross DLL/EXE
            // CRT boundaries, leaving logger_ in an indeterminate state.
            if (auto existing = spdlog::get(name)) {
                logger_ = std::move(existing);
                return;
            }

            std::vector<spdlog::sink_ptr> sinks;

            // Per-logger file sink — plain text, no ANSI codes
            auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                filePath, /*truncate=*/true);
            fileSink->set_formatter(
                logger_detail::makeFormatter<
                    logger_detail::PlainLevelFlag,
                    logger_detail::PlainNameFlag>());
            fileSink->set_level(spdlog::level::trace);
            sinks.push_back(std::move(fileSink));

            // Console sink — colors injected by our custom formatter.
            // Plain stdout sink is used intentionally: the built-in color sink
            // would fight with our own ANSI sequences.
            auto consoleSink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
            consoleSink->set_formatter(
                logger_detail::makeFormatter<
                    logger_detail::ColoredLevelFlag,
                    logger_detail::ColoredNameFlag>());
            consoleSink->set_level(spdlog::level::trace);
            sinks.push_back(std::move(consoleSink));

            // Debugger sink — feeds OutputDebugStringA so every log line appears
            // in CLion's "Debug > Debugger Output" pane when a debugger is attached.
            // This is the only reliable way to see DLL logs when the process is
            // launched via the IDE debug runner (console attachment may be broken).
            // Registered unconditionally so it is ready if a debugger attaches later.
#ifdef _WIN32
            {
                auto debugSink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
                debugSink->set_formatter(
                    logger_detail::makeFormatter<
                        logger_detail::PlainLevelFlag,
                        logger_detail::PlainNameFlag>());
                debugSink->set_level(spdlog::level::trace);
                sinks.push_back(std::move(debugSink));
            }
#endif

            // Shared sink — every logger writes to all.log for cross-module inspection.
            sinks.push_back(allSink);

            logger_ = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
            if (!logger_) return; // make_shared returned null (shouldn't happen, extra guard)

            logger_->set_level(spdlog::level::trace);

            // RelWithDebInfo sets NDEBUG in MSVC, so #ifndef NDEBUG is always false
            // in our standard build profile.  Instead, flush on every message
            // unconditionally — the msvc_sink and file sink need it for visibility
            // during debug sessions.  The marginal I/O cost is acceptable given
            // that we are in a debug/RelWithDebInfo build, not a shipping binary.
            logger_->flush_on(spdlog::level::trace);
            spdlog::register_logger(logger_);
        } catch (...) {
            logger_ = nullptr;
        }
    }

    template<typename... Args>
    void log(spdlog::level::level_enum lvl,
             spdlog::format_string_t<Args...> fmt,
             Args &&... args) const {
        if (logger_) logger_->log(lvl, fmt, std::forward<Args>(args)...);
    }

    // ── Windows: attach/allocate a visible console window ────────────────────
    static void openWindowsConsole() {
#ifdef _WIN32
        // Only redirect stdout/stderr when we open a *new* console.
        // If the process already has a console (console subsystem apps like
        // main.cpp), AttachConsole and AllocConsole both fail — but the
        // handles are already valid, so freopen_s must be skipped.
        // Calling freopen_s in that case reassigns the C-runtime FILE* to a
        // fresh CONOUT$ slot whose handle is different from the one VT
        // processing is set on, which breaks ANSI color rendering.
        const bool attached = AttachConsole(ATTACH_PARENT_PROCESS);

        if (const bool allocated = !attached && AllocConsole(); attached || allocated) {
            FILE *f = nullptr;
            freopen_s(&f, "CONOUT$", "w", stdout);
            freopen_s(&f, "CONOUT$", "w", stderr);
        }

        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);

        // Enable ANSI/VT100 escape code processing — disabled by default on
        // Windows. Must be set on the handle *after* any freopen_s calls.
        if (const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); hOut != INVALID_HANDLE_VALUE) {
            DWORD mode = 0;
            if (GetConsoleMode(hOut, &mode))
                SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
        if (const HANDLE hErr = GetStdHandle(STD_ERROR_HANDLE); hErr != INVALID_HANDLE_VALUE) {
            DWORD mode = 0;
            if (GetConsoleMode(hErr, &mode))
                SetConsoleMode(hErr, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
#endif
    }

    // ── Qt message handler ────────────────────────────────────────────────────
    // Compiled only when Qt is present. Mirrors the spdlog line format so Qt
    // messages look identical to spdlog ones in both file and console.
    // Output: 2026-03-06 11:33:11.766 [WARN ] [QT] file:42 message
#ifdef QT_CORE_LIB
    static void installQtMessageHandler() {
        static QFile s_qtLogFile(QStringLiteral(LOGS_DIR) + "/QT.log");
        if (!s_qtLogFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            return;

        qInstallMessageHandler([](QtMsgType type,
                                  const QMessageLogContext &ctx,
                                  const QString &msg) {
            struct LevelInfo {
                const char *label;
                const char *ansi;
            };
            // Mirror the exact level colors used in levelAnsi()
            static constexpr LevelInfo levels[] = {
                {"DEBUG", "\033[36m"}, // cyan
                {"INFO ", "\033[32m"}, // green
                {"WARN ", "\033[33m"}, // yellow
                {"CRIT ", "\033[31m"}, // red
                {"FATAL", "\033[1;35m"}, // bold magenta
            };
            const int idx = (type >= 0 && type <= 4) ? static_cast<int>(type) : 1;
            const auto &lvl = levels[idx];
            const char *nameClr = logger_detail::nameAnsi("QT");

            const QString ts = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
            const QString location = QString("%1:%2").arg(ctx.file ? ctx.file : "").arg(ctx.line);

            // Plain line → file
            static QTextStream s_fileStream(&s_qtLogFile);
            s_fileStream << ts << " [" << lvl.label << "] [QT] (" << location << ") " << msg << "\n";
            s_fileStream.flush();

            // Colored line → console (only level + name tokens get color)
            QTextStream s_consoleStream(stdout);
            s_consoleStream << ts
                    << " [" << lvl.ansi << lvl.label << logger_detail::RESET << "]"
                    << " [" << nameClr << "QT" << logger_detail::RESET << "]"
                    << " (" << location << ") " << msg << "\n";
            s_consoleStream.flush();

            if (type == QtFatalMsg) abort();
        });
    }
#endif // QT_CORE_LIB

    std::shared_ptr<spdlog::logger> logger_;
    std::string name_;
    std::string filePath_;
};

// =============================================================================
//  Convenience macros
//
//  Per-TU logger selection — define before including this header:
//    #define LOGGER_NAME "NET"   →  logger name "NET" + LOGS_DIR/NET.log
// =============================================================================

#define LOGGER Logger::getInstance(LOGGER_NAME)

#define LOG_TRACE(...)    LOGGER.trace(__VA_ARGS__)
#define LOG_DEBUG(...)    LOGGER.debug(__VA_ARGS__)
#define LOG_INFO(...)     LOGGER.info(__VA_ARGS__)
#define LOG_WARN(...)     LOGGER.warn(__VA_ARGS__)
#define LOG_ERROR(...)    LOGGER.error(__VA_ARGS__)
#define LOG_CRITICAL(...) LOGGER.critical(__VA_ARGS__)

// One-liner named logger:  LOG_INFO_TO("NET", "connected to {}", host)
#define LOG_TRACE_TO(name, ...)    Logger::getInstance(name).trace(__VA_ARGS__)
#define LOG_DEBUG_TO(name, ...)    Logger::getInstance(name).debug(__VA_ARGS__)
#define LOG_INFO_TO(name, ...)     Logger::getInstance(name).info(__VA_ARGS__)
#define LOG_WARN_TO(name, ...)     Logger::getInstance(name).warn(__VA_ARGS__)
#define LOG_ERROR_TO(name, ...)    Logger::getInstance(name).error(__VA_ARGS__)
#define LOG_CRITICAL_TO(name, ...) Logger::getInstance(name).critical(__VA_ARGS__)

#endif //CLOEXTENSIONS_LOGGER_H