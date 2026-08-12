#include "Error.h"

using namespace Chrysalis;

Error::Error(const std::string& message): message_(message){}

std::string_view Error::message() const {
    return message_;
}
