#include "GeneralUIExporterOptionsWidget.h"

#include "ui_GeneralUIExporterOptionsWidget.h"

using namespace UI;

GeneralUIExporterOptionsWidget::GeneralUIExporterOptionsWidget(QWidget *parent) : QWidget(parent),
        ui(new Ui::GeneralUIExporterOptionsWidget) {
    ui->setupUi(this);
    ui->baseUIExporterSettingsBlockContainerWidget->install({ui->customTools, ui->settingsLeftBlockContent, ui->settingsRightBlockContent});
    connect(ui->baseUIExporterSettingsBlockContainerWidget, &BaseUIExporterSettingsBlockContainerWidget::rootFolderChanged, this, &GeneralUIExporterOptionsWidget::rootFolderChanged);
    connect(ui->baseUIExporterSettingsBlockContainerWidget, &BaseUIExporterSettingsBlockContainerWidget::fileNameChanged, this, &GeneralUIExporterOptionsWidget::fileNameChanged);
    connect(ui->baseUIExporterSettingsBlockContainerWidget, &BaseUIExporterSettingsBlockContainerWidget::objectNameChanged, this, &GeneralUIExporterOptionsWidget::objectNameChanged);
    connect(ui->baseUIExporterSettingsBlockContainerWidget, &BaseUIExporterSettingsBlockContainerWidget::classNameChanged, this, &GeneralUIExporterOptionsWidget::classNameChanged);
}

GeneralUIExporterOptionsWidget::~GeneralUIExporterOptionsWidget() {
    delete ui;
}