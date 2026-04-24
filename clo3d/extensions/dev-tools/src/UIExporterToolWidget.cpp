#include "UIExporterToolWidget.h"
#include "ui_UIExporterToolWidget.h"

namespace UI {
    UIExporterToolWidget::UIExporterToolWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UIExporterToolWidget) {
        ui->setupUi(this);
    }

    UIExporterToolWidget::~UIExporterToolWidget() {
        delete ui;
    }
} // UI