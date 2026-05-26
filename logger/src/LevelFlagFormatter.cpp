#include "formatters/LevelFlagFormatter.h"

#include <algorithm>

void LevelFlagFormatter::format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) {
    constexpr static short LOG_LEVEL_LENGTH = 7;
    const auto logLevelView = spdlog::level::to_string_view(msg.level);
    std::string logLevel(logLevelView.begin(), logLevelView.end());
    std::ranges::transform(logLevel, logLevel.begin(), ::toupper);
    logLevel.append(LOG_LEVEL_LENGTH - logLevel.size(), ' ');
    dest.append(logLevel.data(), logLevel.data() + logLevel.size());
}

std::unique_ptr<spdlog::custom_flag_formatter> LevelFlagFormatter::clone() const {
    return std::unique_ptr<custom_flag_formatter>(new LevelFlagFormatter(*this));
}
