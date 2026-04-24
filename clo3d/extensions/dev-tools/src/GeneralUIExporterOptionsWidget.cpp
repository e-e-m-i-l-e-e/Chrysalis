//
// Created by emily on 24/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GeneralUIExporterOptionsWidget.h" resolved

#include "GeneralUIExporterOptionsWidget.h"
#include "ui_GeneralUIExporterOptionsWidget.h"

namespace UI {
    GeneralUIExporterOptionsWidget::GeneralUIExporterOptionsWidget(QWidget *parent) : QWidget(parent),
        ui(new Ui::GeneralUIExporterOptionsWidget) {
        ui->setupUi(this);
    }

    GeneralUIExporterOptionsWidget::~GeneralUIExporterOptionsWidget() {
        delete ui;
    }
} // UI