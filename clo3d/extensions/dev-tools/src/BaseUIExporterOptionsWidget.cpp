#include "BaseUIExporterOptionsWidget.h"

void UI::BaseUIExporterOptionsWidget::read() {
    const auto& baseUIExporterSettings = getBaseUIExporterSettings();
    const auto& options = getOptions();
    baseUIExporterSettings->setRootFolderText(options->getRootFolder().path());
    baseUIExporterSettings->setFileNameText(options->getFileName());
    baseUIExporterSettings->setObjectNameText(options->getObjectName());
    baseUIExporterSettings->setClassNameText(options->getClassName());
}