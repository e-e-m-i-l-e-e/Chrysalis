#include "formatters/ColoredNameFlagFormatter.h"

void ColoredNameFlagFormatter::format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) {
    static constexpr const char* COLOR_PALETTE[] = {
        "\033[34m",  // blue
        "\033[94m",  // bright blue
        "\033[96m",  // bright cyan
        "\033[92m",  // bright green
        "\033[95m",  // bright magenta
        "\033[93m",  // bright yellow
        "\033[91m",  // bright red
        "\033[97m",  // bright white
    };
    static constexpr short COLOR_PALETTE_SIZE = std::size(COLOR_PALETTE);
    static constexpr auto RESET_COLOR = "\033[0m";

    const char* color = COLOR_PALETTE[std::hash<std::string_view>{}(msg.logger_name.data()) % COLOR_PALETTE_SIZE];
    dest.append(color, color + std::strlen(color));
    NameFlagFormatter::format(msg, tm_time, dest);
    dest.append(RESET_COLOR, RESET_COLOR + std::strlen(RESET_COLOR));
}

std::unique_ptr<spdlog::custom_flag_formatter> ColoredNameFlagFormatter::clone() const {
    return std::unique_ptr<custom_flag_formatter>(new ColoredNameFlagFormatter(*this));
}
