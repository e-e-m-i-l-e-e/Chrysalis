//
// Created by emily on 24/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_XmlUIExporterOptionsWidget.h" resolved

#include "../ui/XmlUIExporterOptionsWidget.h"
#include "ui_XmlUIExporterOptionsWidget.h"

namespace UI {
    XmlUIExporterOptionsWidget::XmlUIExporterOptionsWidget(QWidget *parent) : QWidget(parent),
                                                                              ui(new Ui::XmlUIExporterOptionsWidget) {
        ui->setupUi(this);
    }

    XmlUIExporterOptionsWidget::~XmlUIExporterOptionsWidget() {
        delete ui;
    }
} // UI