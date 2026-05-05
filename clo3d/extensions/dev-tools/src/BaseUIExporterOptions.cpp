#include "BaseUIExporterOptions.h"

void BaseUIExporterOptions::read(const Settings &settings) {
    rootFolder_ = QDir(settings.value(Keys::ROOT_FOLDER, Defaults::ROOT_FOLDER.path()).toString());
    fileName_ = settings.value(Keys::FILE_NAME, Defaults::FILE_NAME).toString();
    objectName_ = settings.value(Keys::OBJECT_NAME, Defaults::OBJECT_NAME).toString();
    className_ = settings.value(Keys::CLASS_NAME, Defaults::CLASS_NAME).toString();
}

QDir BaseUIExporterOptions::getRootFolder() const {
    return rootFolder_;
}

QString BaseUIExporterOptions::getFileName() const {
    return fileName_;
}

QString BaseUIExporterOptions::getObjectName() const {
    return objectName_;
}

QString BaseUIExporterOptions::getClassName() const {
    return className_;
}

void BaseUIExporterOptions::setRootFolder(const Settings& settings, const QDir &rootFolder) {
    settings.setValue(Keys::ROOT_FOLDER, rootFolder.path());
    rootFolder_ = rootFolder;
}

void BaseUIExporterOptions::setFileName(const Settings& settings, const QString &fileName) {
    settings.setValue(Keys::FILE_NAME, fileName);
    fileName_ = fileName;
}

void BaseUIExporterOptions::setObjectName(const Settings& settings, const QString &objectName) {
    settings.setValue(Keys::OBJECT_NAME, objectName);
    objectName_ = objectName;
}

void BaseUIExporterOptions::setClassName(const Settings& settings, const QString &className) {
    settings.setValue(Keys::CLASS_NAME, className);
    className_ = className;
}