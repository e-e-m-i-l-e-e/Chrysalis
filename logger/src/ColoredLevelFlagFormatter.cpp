#include "ColoredLevelFlagFormatter.h"

void ColoredLevelFlagFormatter::format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) {
    static constexpr const char* LEVEL_COLORS[7] = {
        "\033[90m",   // trace
        "\033[36m",   // debug
        "\033[32m",   // info
        "\033[33m",   // warn
        "\033[31m",   // err
        "\033[1;35m", // critical
        "\033[0m",    // off
    };
    static constexpr auto RESET_COLOR = "\033[0m";

    const char* levelColor = LEVEL_COLORS[msg.level];
    dest.append(levelColor, levelColor + std::strlen(levelColor));
    LevelFlagFormatter::format(msg, tm_time, dest);
    dest.append(RESET_COLOR, RESET_COLOR + std::strlen(RESET_COLOR));
}

std::unique_ptr<spdlog::custom_flag_formatter> ColoredLevelFlagFormatter::clone() const {
    return std::unique_ptr<custom_flag_formatter>(new ColoredLevelFlagFormatter(*this));
}
