#include "LoggingToolSettingsWidget.h"

#include <iostream>

#include "ui_LoggingToolSettingsWidget.h"

#include <QComboBox>

#include "LogLevelDelegate.h"

using namespace UI;

LoggingToolSettingsWidget::LoggingToolSettingsWidget(LoggingToolSettings* settings, LoggerRegistryModel* registryModel, QStackedWidget* sinks, QWidget *parent)
: BaseExtensionSettingsWidget(settings, parent), ui(new Ui::LoggingToolSettingsWidget), settings_(settings), registryModel_(registryModel) {
    ui->setupUi(this);
    ui->table->setItemDelegateForColumn(1, new LogLevelDelegate(this));
    ui->table->setModel(registryModel_);
    ui->table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    for (int row = 0; row < registryModel_->rowCount({}); ++row) {
        ui->table->openPersistentEditor(registryModel_->index(row, 1));
    }
    this->layout()->addWidget(sinks);
    connect(ui->table->selectionModel(), &QItemSelectionModel::currentRowChanged, this,
        [=](const QModelIndex& current, const QModelIndex&) {
            if (current.column() != 0) return;
            sinks->setCurrentIndex(current.row() + 1);
        }
    );
}

LoggingToolSettingsWidget::~LoggingToolSettingsWidget() {
    delete ui;
}