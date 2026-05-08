#include "BaseUIExporterOptionsWidget.h"

QString UI::BaseUIExporterOptionsWidget::getTitle() {
    return getBaseUIExporterSettings()->getTitle();
}

void UI::BaseUIExporterOptionsWidget::write() {
    const auto& baseUIExporterSettings = getBaseUIExporterSettings();
    const auto& options = getOptions();
    options->setRootFolder(baseUIExporterSettings->getRootFolderText());
    options->setFileName(baseUIExporterSettings->getFileNameText());
    options->setObjectName(baseUIExporterSettings->getObjectNameText());
    options->setClassName(baseUIExporterSettings->getClassNameText());
}

void UI::BaseUIExporterOptionsWidget::read() {
    const auto& baseUIExporterSettings = getBaseUIExporterSettings();
    const auto& options = getOptions();
    baseUIExporterSettings->setRootFolderText(options->getRootFolder().path());
    baseUIExporterSettings->setFileNameText(options->getFileName());
    baseUIExporterSettings->setObjectNameText(options->getObjectName());
    baseUIExporterSettings->setClassNameText(options->getClassName());
}