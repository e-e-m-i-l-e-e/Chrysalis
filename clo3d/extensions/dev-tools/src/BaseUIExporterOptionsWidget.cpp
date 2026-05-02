#include "BaseUIExporterOptionsWidget.h"

QString UI::BaseUIExporterOptionsWidget::getTitle() {
    return getBaseUIExporterSettings()->getTitle();
}

void UI::BaseUIExporterOptionsWidget::write(QSettings *settings) {
    const auto& baseUIExporterSettings = getBaseUIExporterSettings();
    const auto& options = getOptions();
    options->setRootFolder(settings, baseUIExporterSettings->getRootFolderText());
    options->setFileName(settings, baseUIExporterSettings->getFileNameText());
    options->setObjectName(settings, baseUIExporterSettings->getObjectNameText());
    options->setClassName(settings, baseUIExporterSettings->getClassNameText());
}

void UI::BaseUIExporterOptionsWidget::read(QSettings* settings) {
    const auto& baseUIExporterSettings = getBaseUIExporterSettings();
    const auto& options = getOptions();
    baseUIExporterSettings->setRootFolderText(options->getRootFolder(settings).path());
    baseUIExporterSettings->setFileNameText(options->getFileName(settings));
    baseUIExporterSettings->setObjectNameText(options->getObjectName(settings));
    baseUIExporterSettings->setClassNameText(options->getClassName(settings));
}
