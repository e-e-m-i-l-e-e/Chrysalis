#ifndef CHRYSALIS_COLOREDNAMEFLAG_H
#define CHRYSALIS_COLOREDNAMEFLAG_H

#include <spdlog/pattern_formatter.h>

class NameFlagFormatter: public spdlog::custom_flag_formatter {
public:
    void format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) override;
    [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override;
};

#endif //CHRYSALIS_COLOREDNAMEFLAG_H