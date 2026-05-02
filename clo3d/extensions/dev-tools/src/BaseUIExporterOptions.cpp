#include "BaseUIExporterOptions.h"

QDir BaseUIExporterOptions::getRootFolder(const QSettings* settings) {
    return QDir(settings->value("rootFolder", QString(CLO_HOME) + "/extensions").toString());
}

QString BaseUIExporterOptions::getFileName(QSettings* settings) {
    return settings->value("fileName", "ui").toString();
}

QString BaseUIExporterOptions::getObjectName(QSettings* settings) {
    return settings->value("objectName", "").toString();
}

QString BaseUIExporterOptions::getClassName(QSettings* settings) {
    return settings->value("className", "").toString();
}

void BaseUIExporterOptions::setRootFolder(QSettings *settings, const QDir &rootFolder) {
    settings->setValue("rootFolder", rootFolder.path());
}

void BaseUIExporterOptions::setFileName(QSettings *settings, const QString &fileName) {
    settings->setValue("fileName", fileName);
}

void BaseUIExporterOptions::setObjectName(QSettings *settings, const QString &objectName) {
    settings->setValue("objectName", objectName);
}

void BaseUIExporterOptions::setClassName(QSettings *settings, const QString &className) {
    settings->setValue("className", className);
}
