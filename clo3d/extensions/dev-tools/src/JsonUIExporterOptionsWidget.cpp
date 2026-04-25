#include "JsonUIExporterOptionsWidget.h"
#include "ui_JsonUIExporterOptionsWidget.h"

namespace UI {
    JsonUIExporterOptionsWidget::JsonUIExporterOptionsWidget(QWidget *parent) : QWidget(parent),
        ui(new Ui::JsonUIExporterOptionsWidget) {
        ui->setupUi(this);
        ui->baseUIExporterSettingsBlockContainerWidget->install({ui->customTools, ui->settingsLeftBlockContent, ui->settingsRightBlockContent});
    }

    JsonUIExporterOptionsWidget::~JsonUIExporterOptionsWidget() {
        delete ui;
    }
} // UI