#include "JsonUIExporterOptionsWidget.h"
#include "ui_JsonUIExporterOptionsWidget.h"

namespace UI {
    JsonUIExporterOptionsWidget::JsonUIExporterOptionsWidget(QWidget *parent) : QWidget(parent),
        ui(new Ui::JsonUIExporterOptionsWidget) {
        ui->setupUi(this);
    }

    JsonUIExporterOptionsWidget::~JsonUIExporterOptionsWidget() {
        delete ui;
    }
} // UI