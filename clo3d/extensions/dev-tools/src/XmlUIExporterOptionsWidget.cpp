#include "XmlUIExporterOptionsWidget.h"
#include "ui_XmlUIExporterOptionsWidget.h"

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
}
