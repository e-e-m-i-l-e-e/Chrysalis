#include "BaseUIExporterOptions.h"

QDir BaseUIExporterOptions::getRootFolder(const Settings& settings) {
    return QDir(settings.value("rootFolder", QString(CLO_HOME) + "/extensions").toString());
}

QString BaseUIExporterOptions::getFileName(Settings& settings) {
    return settings.value("fileName", "ui").toString();
}

QString BaseUIExporterOptions::getObjectName(Settings& settings) {
    return settings.value("objectName", "").toString();
}

QString BaseUIExporterOptions::getClassName(Settings& settings) {
    return settings.value("className", "").toString();
}

void BaseUIExporterOptions::setRootFolder(Settings& settings, const QDir &rootFolder) {
    settings.setValue("rootFolder", rootFolder.path());
}

void BaseUIExporterOptions::setFileName(Settings& settings, const QString &fileName) {
    settings.setValue("fileName", fileName);
}

void BaseUIExporterOptions::setObjectName(Settings& settings, const QString &objectName) {
    settings.setValue("objectName", objectName);
}

void BaseUIExporterOptions::setClassName(Settings& settings, const QString &className) {
    settings.setValue("className", className);
}
