#include "LoggingToolSettingsWidget.h"
#include "ui_LoggingToolSettingsWidget.h"

using namespace UI;

LoggingToolSettingsWidget::LoggingToolSettingsWidget(LoggingToolSettings* settings, QWidget *parent)
: BaseExtensionSettingsWidget(settings, parent), ui(new Ui::LoggingToolSettingsWidget), settings_(settings) {
    ui->setupUi(this);
}

LoggingToolSettingsWidget::~LoggingToolSettingsWidget() {
    delete ui;
}