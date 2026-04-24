#include "XmlUIExporterOptionsWidget.h"
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