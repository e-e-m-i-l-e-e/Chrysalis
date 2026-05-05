#include "XmlUIExporterOptionsWidget.h"
#include "ui_XmlUIExporterOptionsWidget.h"

#include "Logger.h"

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

void XmlUIExporterOptionsWidget::read(Settings& settings) {
    if (!options_) {
        LOG_WARN("XML UI Exporter options weren't set");
        this->setEnabled(false);
        return;
    }
    BaseUIExporterOptionsWidget::read(settings);
    ui->exportIcons->setChecked(options_->getExportIcons());
    ui->uiCompatible->setChecked(options_->getUICompatible());
}

std::shared_ptr<BaseUIExporterOptions> XmlUIExporterOptionsWidget::getOptions() {
    return options_;
}

void XmlUIExporterOptionsWidget::setOptions(const std::shared_ptr<BaseUIExporterOptions> options) {
    options_ = std::dynamic_pointer_cast<XmlUIExporterOptions>(options);
}

BaseUIExporterSettingsBlockContainerWidget* XmlUIExporterOptionsWidget::getBaseUIExporterSettings() {
    return ui->baseUIExporterSettingsBlockContainerWidget;
}
