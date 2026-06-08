#include "ExportPatternCommand.h"

#include "CLOAPIInterface.h"

#include "Logging.h"
#define LOGGER_NAME "Export Pattern Command"

ExportPatternCommand::ExportPatternCommand(ExportPatternCommandArguments* arguments): BaseCommand(arguments) {}

void ExportPatternCommand::run() {
    const auto arguments = dynamic_cast<ExportPatternCommandArguments*>(arguments_);
    const std::string filePath = arguments->getFilePath().toStdString();
    LOG_INFO("Exporting pattern into {}", filePath);
    if (!PATTERN_API->ExportPatternJSON(filePath)) {
        LOG_ERROR("Filed to export pattern.");
    } else {
        LOG_INFO("Pattern was imported successfully into \"{}\"", filePath);
    }
}
