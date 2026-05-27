#ifndef FASHIONDESIGNAPPS_COLOREDNAMEFLAGFORMATTER_H
#define FASHIONDESIGNAPPS_COLOREDNAMEFLAGFORMATTER_H

#include "NameFlagFormatter.h"

class ColoredNameFlagFormatter: public NameFlagFormatter {
public:
    void format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) override;
    [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override;
};

#endif //FASHIONDESIGNAPPS_COLOREDNAMEFLAGFORMATTER_H