#include "ExportPatternCommandArguments.h"

using namespace CLO3D;

ExportPatternCommandArguments::ExportPatternCommandArguments(QSettings* settings): BaseCommandArguments(settings) {}

void ExportPatternCommandArguments::read() {
    filePath_ = settings_->value(Keys::FILE_PATH, Defaults::FILE_PATH).toString();
}

void ExportPatternCommandArguments::write() {
    settings_->setValue(Keys::FILE_PATH, filePath_);
}

const QString& ExportPatternCommandArguments::getFilePath() const {
    return filePath_;
}

void ExportPatternCommandArguments::setFilePath(const QString& filePath) {
    filePath_ = filePath;
}

QString ExportPatternCommandArguments::getName() {
    return NAME;
}