#include "BaseUIExporterOptions.h"

#include <iostream>

using namespace CLO3D;

bool BaseUIExporterOptions::isEnabled() {
    return true;
}

void BaseUIExporterOptions::read(const QSettings* settings) {
    setRootFolder(QDir(settings->value(Keys::ROOT_FOLDER, Defaults::ROOT_FOLDER.path()).toString()));
    setFileName(settings->value(Keys::FILE_NAME, Defaults::FILE_NAME).toString());
    setObjectName(settings->value(Keys::OBJECT_NAME, Defaults::OBJECT_NAME).toString());
    setClassName(settings->value(Keys::CLASS_NAME, Defaults::CLASS_NAME).toString());
}

void BaseUIExporterOptions::write(QSettings* settings) {
    settings->setValue(Keys::ROOT_FOLDER, rootFolder_.path());
    settings->setValue(Keys::FILE_NAME, fileName_);
    settings->setValue(Keys::OBJECT_NAME, objectName_);
    settings->setValue(Keys::CLASS_NAME, className_);
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

void BaseUIExporterOptions::setRootFolder(const QDir &rootFolder) {
    rootFolder_ = rootFolder;
}

void BaseUIExporterOptions::setFileName(const QString &fileName) {
    fileName_ = fileName;
}

void BaseUIExporterOptions::setObjectName(const QString &objectName) {
    objectName_ = objectName;
}

void BaseUIExporterOptions::setClassName(const QString &className) {
    className_ = className;
}