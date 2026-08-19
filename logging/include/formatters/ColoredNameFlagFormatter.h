#ifndef CHRYSALIS_COLOREDNAMEFLAGFORMATTER_H
#define CHRYSALIS_COLOREDNAMEFLAGFORMATTER_H

#include <ctime>
#include <memory>

#include <spdlog/common.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/pattern_formatter.h>

#include "LoggingLibraryExport.h"
#include "formatters/NameFlagFormatter.h"

namespace Logging {
    class LOGGING ColoredNameFlagFormatter: public NameFlagFormatter {
    public:
        void format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) override;
        [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override;
    };
}

#endif //CHRYSALIS_COLOREDNAMEFLAGFORMATTER_H