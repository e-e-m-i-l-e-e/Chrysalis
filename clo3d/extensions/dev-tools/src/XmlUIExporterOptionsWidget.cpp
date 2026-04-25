#include "XmlUIExporterOptionsWidget.h"
#include "ui_XmlUIExporterOptionsWidget.h"

using namespace UI;

XmlUIExporterOptionsWidget::XmlUIExporterOptionsWidget(QWidget *parent) : QWidget(parent),
                                                                             ui(new Ui::XmlUIExporterOptionsWidget) {
    ui->setupUi(this);
    ui->baseUIExporterSettingsBlockContainerWidget->install({ui->customTools, ui->settingsLeftBlockContent, ui->settingsRightBlockContent});
}

XmlUIExporterOptionsWidget::~XmlUIExporterOptionsWidget() {
    delete ui;
}

void XmlUIExporterOptionsWidget::rootFolderChanged(const QString &rootFolder) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setRootFolder(rootFolder);
}

void XmlUIExporterOptionsWidget::fileNameChanged(const QString &fileName) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setFileName(fileName);
}

void XmlUIExporterOptionsWidget::objectNameChanged(const QString &objectName) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setObjectName(objectName);
}

void XmlUIExporterOptionsWidget::classNameChanged(const QString &className) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setClassName(className);
}
