#include "exceptions/ProjectIOError.h"

using namespace Chrysalis;

ProjectIOError::ProjectIOError(const std::string& filePath): std::runtime_error(filePath) {}
