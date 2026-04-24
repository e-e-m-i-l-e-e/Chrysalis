//
// Created by emily on 24/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoggingToolWidget.h" resolved

#include "../include/LoggingToolWidget.h"
#include "ui_LoggingToolWidget.h"

namespace UI {
    LoggingToolWidget::LoggingToolWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LoggingToolWidget) {
        ui->setupUi(this);
    }

    LoggingToolWidget::~LoggingToolWidget() {
        delete ui;
    }
} // UI