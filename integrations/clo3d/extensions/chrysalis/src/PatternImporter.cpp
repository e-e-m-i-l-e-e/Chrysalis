#include "PatternImporter.h"

#include "Logging.h"
#define LOGGER_NAME "Pattern Importer"

using namespace Chrysalis;

PatternImporter::PatternImporter(Project* project): project_(project) {}

void PatternImporter::import() const {
    LOG_INFO("Importing pattern from project: {}", project_->getName());
}
