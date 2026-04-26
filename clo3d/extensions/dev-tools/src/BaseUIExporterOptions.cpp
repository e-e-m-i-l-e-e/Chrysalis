#include "BaseUIExporterOptions.h"

BaseUIExporterOptions::BaseUIExporterOptions(const QSettings* settings)
    : settings_(settings) {}

BaseUIExporterOptions::~BaseUIExporterOptions() {
    delete settings_;
}

QDir BaseUIExporterOptions::getRootFolder() {
    return QDir::current();
}

QString BaseUIExporterOptions::getFileName() {
    return "test";
}

QString BaseUIExporterOptions::getObjectName() {
    return "BaseUIExporterOptions";
}

QString BaseUIExporterOptions::getClassName() {
    return "BaseUIExporterOptions";
}
