#include "UIExporterToolWidget.h"
#include "ui_UIExporterToolWidget.h"

using namespace UI;

UIExporterToolWidget::UIExporterToolWidget(QWidget *parent) : NamedWidget(parent), ui(new Ui::UIExporterToolWidget) {
    ui->setupUi(this);

    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::rootFolderChanged,
            ui->jsonUIExporterOptionsWidget, &JsonUIExporterOptionsWidget::rootFolderChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::fileNameChanged,
            ui->jsonUIExporterOptionsWidget, &JsonUIExporterOptionsWidget::fileNameChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::objectNameChanged,
            ui->jsonUIExporterOptionsWidget, &JsonUIExporterOptionsWidget::objectNameChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::classNameChanged,
            ui->jsonUIExporterOptionsWidget, &JsonUIExporterOptionsWidget::classNameChanged);

    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::rootFolderChanged,
            ui->xmlUIExporterOptionsWidget, &XmlUIExporterOptionsWidget::rootFolderChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::fileNameChanged,
            ui->xmlUIExporterOptionsWidget, &XmlUIExporterOptionsWidget::fileNameChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::objectNameChanged,
            ui->xmlUIExporterOptionsWidget, &XmlUIExporterOptionsWidget::objectNameChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::classNameChanged,
            ui->xmlUIExporterOptionsWidget, &XmlUIExporterOptionsWidget::classNameChanged);
}

UIExporterToolWidget::~UIExporterToolWidget() {
    delete ui;
}