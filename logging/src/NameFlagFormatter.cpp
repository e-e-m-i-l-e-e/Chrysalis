#include "formatters/NameFlagFormatter.h"

#include <ctime>
#include <string>
#include <memory>

#include <spdlog/common.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/pattern_formatter.h>

#include "Logger.h"

using namespace Logging;

void NameFlagFormatter::format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) {
    std::string name(msg.logger_name.begin(), msg.logger_name.end());
    if (name.length() < Logger::LOGGER_NAME_LENGTH) {
        name.append(Logger::LOGGER_NAME_LENGTH - name.length(), ' ');
    } else if (name.length() > Logger::LOGGER_NAME_LENGTH) {
        name = name.substr(0, Logger::LOGGER_NAME_LENGTH - 3) + "...";
    }
    dest.append(name);
}

std::unique_ptr<spdlog::custom_flag_formatter> NameFlagFormatter::clone() const {
    return std::unique_ptr<custom_flag_formatter>(new NameFlagFormatter(*this));
}
