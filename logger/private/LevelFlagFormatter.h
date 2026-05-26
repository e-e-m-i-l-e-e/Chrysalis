#ifndef FASHIONDESIGNAPPS_PLAINLEVELFLAG_H
#define FASHIONDESIGNAPPS_PLAINLEVELFLAG_H

#include <spdlog/pattern_formatter.h>

class LevelFlagFormatter: public spdlog::custom_flag_formatter {
public:
    void format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) override;
    [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override;
};

#endif //FASHIONDESIGNAPPS_PLAINLEVELFLAG_H