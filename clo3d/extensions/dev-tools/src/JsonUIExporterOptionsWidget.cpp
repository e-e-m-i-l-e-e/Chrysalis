#include "JsonUIExporterOptionsWidget.h"
#include "ui_JsonUIExporterOptionsWidget.h"

using namespace UI;

JsonUIExporterOptionsWidget::JsonUIExporterOptionsWidget(QWidget *parent) : QWidget(parent),
        ui(new Ui::JsonUIExporterOptionsWidget) {
    ui->setupUi(this);
    ui->baseUIExporterSettingsBlockContainerWidget->install({ui->customTools, ui->settingsLeftBlockContent, ui->settingsRightBlockContent});
}

JsonUIExporterOptionsWidget::~JsonUIExporterOptionsWidget() {
    delete ui;
}

void JsonUIExporterOptionsWidget::rootFolderChanged(const QString &rootFolder) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setRootFolder(rootFolder);
}

void JsonUIExporterOptionsWidget::fileNameChanged(const QString &fileName) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setFileName(fileName);
}

void JsonUIExporterOptionsWidget::objectNameChanged(const QString &objectName) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setObjectName(objectName);
}

void JsonUIExporterOptionsWidget::classNameChanged(const QString &className) const {
    ui->baseUIExporterSettingsBlockContainerWidget->setClassName(className);
}
