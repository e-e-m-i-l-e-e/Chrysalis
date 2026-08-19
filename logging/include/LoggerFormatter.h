#ifndef CHRYSALIS_LOGGERFORMATTER_H
#define CHRYSALIS_LOGGERFORMATTER_H

#include <spdlog/sinks/sink.h>
#include <spdlog/pattern_formatter.h>

namespace Logging {
    template<typename NameFormatter, typename LevelFormatter>
    class LoggerFormatter {
    public:
        static void apply(const std::shared_ptr<spdlog::sinks::sink>& sink) {
            static constexpr auto PATTERN = "%Y-%m-%d %H:%M:%S.%e [%*] [%&] %v";

            auto formatter = std::make_unique<spdlog::pattern_formatter>();
            formatter->add_flag<NameFormatter>('&');
            formatter->add_flag<LevelFormatter>('*');
            formatter->set_pattern(PATTERN);

            sink->set_formatter(std::move(formatter));
        }
    };
}

#endif //CHRYSALIS_LOGGERFORMATTER_H