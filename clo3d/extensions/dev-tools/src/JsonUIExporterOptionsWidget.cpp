#include "JsonUIExporterOptionsWidget.h"
#include "ui_JsonUIExporterOptionsWidget.h"

#include "Logger.h"

#define LOGGER_NAME "UI Exporter Options"

using namespace UI;

JsonUIExporterOptionsWidget::JsonUIExporterOptionsWidget(QWidget *parent)
    : BaseUIExporterOptionsWidget(parent),
      ui(new Ui::JsonUIExporterOptionsWidget) {
    ui->setupUi(this);
    ui->baseUIExporterSettingsBlockContainerWidget->install({ui->customTools, ui->settingsLeftBlockContent, ui->settingsRightBlockContent});
}

JsonUIExporterOptionsWidget::~JsonUIExporterOptionsWidget() {
    delete ui;
}

void JsonUIExporterOptionsWidget::rootFolderChanged(const QString &rootFolder) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setRootFolderText(rootFolder);
}

void JsonUIExporterOptionsWidget::fileNameChanged(const QString &fileName) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setFileNameText(fileName);
}

void JsonUIExporterOptionsWidget::objectNameChanged(const QString &objectName) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setObjectNameText(objectName);
}

void JsonUIExporterOptionsWidget::classNameChanged(const QString &className) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setClassNameText(className);
}

void JsonUIExporterOptionsWidget::read() {
    if (!options_) {
        LOG_WARN("Json UI Exporter options weren't set");
        this->setEnabled(false);
        return;
    }
}

void JsonUIExporterOptionsWidget::setOptions(const std::shared_ptr<BaseUIExporterOptions> options) {
    options_ = std::dynamic_pointer_cast<JsonUIExporterOptions>(options);
}
