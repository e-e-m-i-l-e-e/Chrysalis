#include "XmlUIExporterOptionsWidget.h"
#include "ui_XmlUIExporterOptionsWidget.h"

#include "Logging.h"

#define LOGGER_NAME "UI Exporter Options"

using namespace UI;

XmlUIExporterOptionsWidget::XmlUIExporterOptionsWidget(QWidget *parent)
    : BaseUIExporterOptionsWidget(parent),
      ui(new Ui::XmlUIExporterOptionsWidget) {
    ui->setupUi(this);
    ui->baseUIExporterSettingsBlockContainerWidget->install({ui->customTools, ui->settingsLeftBlockContent, ui->settingsRightBlockContent});
}

XmlUIExporterOptionsWidget::~XmlUIExporterOptionsWidget() {
    delete ui;
}

void XmlUIExporterOptionsWidget::rootFolderChanged(const QString &rootFolder) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setRootFolderText(rootFolder);
}

void XmlUIExporterOptionsWidget::fileNameChanged(const QString &fileName) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setFileNameText(fileName);
}

void XmlUIExporterOptionsWidget::objectNameChanged(const QString &objectName) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setObjectNameText(objectName);
}

void XmlUIExporterOptionsWidget::classNameChanged(const QString &className) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setClassNameText(className);
}

void XmlUIExporterOptionsWidget::read() {
    if (!options_) {
        LOG_WARN("XML UI Exporter options weren't set");
        this->setEnabled(false);
        return;
    }
    BaseUIExporterOptionsWidget::read();
    ui->isEnabled->setChecked(options_->isEnabled());
    ui->exportIcons->setChecked(options_->getExportIcons());
    ui->uiCompatible->setChecked(options_->getUICompatible());
}

void XmlUIExporterOptionsWidget::write() {
    BaseUIExporterOptionsWidget::write();
    options_->setIsEnabled(ui->isEnabled->isChecked());
    options_->setExportIcons(ui->exportIcons->isChecked());
    options_->setUICompatible(ui->uiCompatible->isChecked());
}

BaseUIExporterOptions* XmlUIExporterOptionsWidget::getOptions() {
    return options_;
}

void XmlUIExporterOptionsWidget::setOptions(BaseUIExporterOptions* options) {
    options_ = dynamic_cast<XmlUIExporterOptions*>(options);
}

BaseUIExporterSettingsBlockContainerWidget* XmlUIExporterOptionsWidget::getBaseUIExporterSettings() {
    return ui->baseUIExporterSettingsBlockContainerWidget;
}
