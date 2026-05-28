#include "LoggingToolSettingsWidget.h"

#include <iostream>

#include "ui_LoggingToolSettingsWidget.h"

#include <QFileDialog>
#include <QDesktopServices>

#include "LogLevelDelegate.h"

using namespace UI;

LoggingToolSettingsWidget::LoggingToolSettingsWidget(LoggingToolSettings* settings, LoggerRegistryModel* registryModel, QStackedWidget* sinks, QWidget *parent)
: BaseExtensionSettingsWidget(settings, parent), ui(new Ui::LoggingToolSettingsWidget), sinks_(sinks), settings_(settings), registryModel_(registryModel) {
    ui->setupUi(this);
    ui->table->setModel(registryModel_);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table->setItemDelegateForColumn(1, new LogLevelDelegate(registryModel_));
    ui->table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->table->setEditTriggers(QAbstractItemView::CurrentChanged);
    for (int row = 0; row < registryModel->rowCount({}); row++) {
        ui->table->openPersistentEditor(registryModel->index(row, 1));
    }
    this->layout()->addWidget(sinks_);
    resetSelection();

    connect(ui->commonFileButton, &QPushButton::clicked, this, &LoggingToolSettingsWidget::resetSelection);
    connect(ui->openInEditorButton, &QPushButton::clicked, this, &LoggingToolSettingsWidget::openInEditor);
    connect(ui->folderButton, &QToolButton::clicked, this, &LoggingToolSettingsWidget::chooseLoggingDirectory);
    connect(ui->table->selectionModel(), &QItemSelectionModel::currentRowChanged, this,
            [this](const QModelIndex& current, const QModelIndex&)
            {
                sinks_->setCurrentIndex(current.row() + 1);
                if (current.column() == 0) ui->loggerFileLocation->setText(
                    settings_->getLoggerFileLocation(current.data().toString()));
            }
    );
}

LoggingToolSettingsWidget::~LoggingToolSettingsWidget() {
    this->layout()->removeWidget(sinks_);
    sinks_->setParent(nullptr);
    delete ui;
}

void LoggingToolSettingsWidget::read() {
    BaseExtensionSettingsWidget::read();
    ui->commonFileName->setText(settings_->getCommonFileName());
    ui->loggingDirectory->setText(settings_->getLoggingDirectory());
    ui->loggerFileLocation->setText(settings_->getLoggerFileLocation());
}

void LoggingToolSettingsWidget::write() {
    BaseExtensionSettingsWidget::write();
}

void LoggingToolSettingsWidget::flush() const {
    if (sinks_->currentIndex() == 0) settings_->flush();
    else settings_->flush(sinks_->currentIndex() - 1);
}

void LoggingToolSettingsWidget::openInEditor() const {
    flush();
    QDesktopServices::openUrl(QUrl::fromLocalFile(ui->loggerFileLocation->text()));
}

void LoggingToolSettingsWidget::resetSelection() const {
    sinks_->setCurrentIndex(0);
    ui->table->setCurrentIndex({});
    ui->loggerFileLocation->setText(settings_->getLoggerFileLocation());
}

void LoggingToolSettingsWidget::chooseLoggingDirectory() {
    static constexpr auto LOGGING_FOLDER_PROMPT = "Choose logging folder";
    if (const QString directory = QFileDialog::getExistingDirectory(this, LOGGING_FOLDER_PROMPT,
                                                                    ui->loggingDirectory->text(),
                                                                    QFileDialog::ShowDirsOnly); !directory.isEmpty()) {
        ui->loggingDirectory->setText(directory);
    }
}
