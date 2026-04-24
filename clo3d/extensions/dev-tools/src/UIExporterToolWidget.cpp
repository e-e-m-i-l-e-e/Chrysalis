//
// Created by emily on 24/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UIExporterToolWidget.h" resolved

#include "../ui/UIExporterToolWidget.h"
#include "ui_UIExporterToolWidget.h"

namespace UI {
    UIExporterToolWidget::UIExporterToolWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UIExporterToolWidget) {
        ui->setupUi(this);
    }

    UIExporterToolWidget::~UIExporterToolWidget() {
        delete ui;
    }
} // UI