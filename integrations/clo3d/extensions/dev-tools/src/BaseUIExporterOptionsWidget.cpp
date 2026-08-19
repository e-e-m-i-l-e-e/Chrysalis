#include "BaseUIExporterOptionsWidget.h"

using namespace CLO3D::UI;

QString BaseUIExporterOptionsWidget::getTitle() {
    return getBaseUIExporterSettings()->getTitle();
}

void BaseUIExporterOptionsWidget::write() {
    const auto& baseUIExporterSettings = getBaseUIExporterSettings();
    const auto& options = getOptions();
    options->setRootFolder(baseUIExporterSettings->getRootFolderText());
    options->setFileName(baseUIExporterSettings->getFileNameText());
    options->setObjectName(baseUIExporterSettings->getObjectNameText());
    options->setClassName(baseUIExporterSettings->getClassNameText());
}

void BaseUIExporterOptionsWidget::read() {
    const auto& baseUIExporterSettings = getBaseUIExporterSettings();
    const auto& options = getOptions();
    baseUIExporterSettings->setRootFolderText(options->getRootFolder().path());
    baseUIExporterSettings->setFileNameText(options->getFileName());
    baseUIExporterSettings->setObjectNameText(options->getObjectName());
    baseUIExporterSettings->setClassNameText(options->getClassName());
}