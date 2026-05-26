#ifndef FASHIONDESIGNAPPS_COLOREDLEVELFLAG_H
#define FASHIONDESIGNAPPS_COLOREDLEVELFLAG_H

#include "LevelFlagFormatter.h"

class ColoredLevelFlagFormatter: public LevelFlagFormatter {
public:
    void format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) override;
    [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override;
};

#endif //FASHIONDESIGNAPPS_COLOREDLEVELFLAG_H