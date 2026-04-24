//
// Created by emily on 24/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_JsonUIExporterOptionsWidget.h" resolved

#include "../ui/JsonUIExporterOptionsWidget.h"
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