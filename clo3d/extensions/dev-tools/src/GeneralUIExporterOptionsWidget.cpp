#include "GeneralUIExporterOptionsWidget.h"

#include "Logger.h"
#include "ui_GeneralUIExporterOptionsWidget.h"

#define LOGGER_NAME "UI Exporter Options"

using namespace UI;

GeneralUIExporterOptionsWidget::GeneralUIExporterOptionsWidget(QWidget *parent)
    : BaseUIExporterOptionsWidget(parent),
      ui(new Ui::GeneralUIExporterOptionsWidget) {
    ui->setupUi(this);
    ui->baseUIExporterSettingsBlockContainerWidget->install({ui->customTools, ui->settingsLeftBlockContent, ui->settingsRightBlockContent});
    connect(ui->baseUIExporterSettingsBlockContainerWidget, &BaseUIExporterSettingsBlockContainerWidget::rootFolderChanged,
        this, &GeneralUIExporterOptionsWidget::rootFolderChanged);
    connect(ui->baseUIExporterSettingsBlockContainerWidget, &BaseUIExporterSettingsBlockContainerWidget::fileNameChanged,
        this, &GeneralUIExporterOptionsWidget::fileNameChanged);
    connect(ui->baseUIExporterSettingsBlockContainerWidget, &BaseUIExporterSettingsBlockContainerWidget::objectNameChanged,
        this, &GeneralUIExporterOptionsWidget::objectNameChanged);
    connect(ui->baseUIExporterSettingsBlockContainerWidget, &BaseUIExporterSettingsBlockContainerWidget::classNameChanged,
        this, &GeneralUIExporterOptionsWidget::classNameChanged);
}

GeneralUIExporterOptionsWidget::~GeneralUIExporterOptionsWidget() {
    delete ui;
}

void GeneralUIExporterOptionsWidget::read() {
    if (!options_) {
        LOG_WARN("General UI Exporter options weren't set");
        this->setEnabled(false);
        return;
    }
    ui->keySequenceEdit->setKeySequence(options_->getKeySequence());
}

void GeneralUIExporterOptionsWidget::setOptions(const std::shared_ptr<BaseUIExporterOptions> options) {
    options_ = std::dynamic_pointer_cast<GeneralUIExporterOptions>(options);
}