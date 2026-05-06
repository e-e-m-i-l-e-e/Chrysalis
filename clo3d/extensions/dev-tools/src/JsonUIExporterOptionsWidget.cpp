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
    BaseUIExporterOptionsWidget::read();
    ui->isEnabled->setChecked(options_->getIsEnabled());
    ui->visibleOnly->setChecked(options_->getVisibleOnly());
    ui->ignoreCSS->setChecked(options_->getIgnoreCSS());
}

void JsonUIExporterOptionsWidget::write() {
    BaseUIExporterOptionsWidget::write();
    options_->setIsEnabled(ui->isEnabled->isChecked());
    options_->setVisibleOnly(ui->visibleOnly->isChecked());
    options_->setIgnoreCSS(ui->ignoreCSS->isChecked());
}

BaseUIExporterOptions* JsonUIExporterOptionsWidget::getOptions() {
    return options_;
}

void JsonUIExporterOptionsWidget::setOptions(BaseUIExporterOptions* options) {
    options_ = dynamic_cast<JsonUIExporterOptions*>(options);
}

BaseUIExporterSettingsBlockContainerWidget* JsonUIExporterOptionsWidget::getBaseUIExporterSettings() {
    return ui->baseUIExporterSettingsBlockContainerWidget;
}
