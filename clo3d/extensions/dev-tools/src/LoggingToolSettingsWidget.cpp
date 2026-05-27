#include "LoggingToolSettingsWidget.h"
#include "ui_LoggingToolSettingsWidget.h"

#include <QUrl>
#include <QComboBox>
#include <QDesktopServices>

#include "LogLevelDelegate.h"

using namespace UI;

LoggingToolSettingsWidget::LoggingToolSettingsWidget(LoggingToolSettings* settings, LoggerRegistryModel* registryModel, QStackedWidget* sinks, QWidget *parent)
: BaseExtensionSettingsWidget(settings, parent), ui(new Ui::LoggingToolSettingsWidget), settings_(settings), registryModel_(registryModel) {
    ui->setupUi(this);
    ui->table->setModel(registryModel_);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table->setItemDelegateForColumn(1, new LogLevelDelegate(this));
    ui->table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->table->setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::SelectedClicked);

    this->layout()->addWidget(sinks);
    connect(ui->table->selectionModel(), &QItemSelectionModel::currentRowChanged, this,
        [=, this](const QModelIndex& current, const QModelIndex&) {
            sinks->setCurrentIndex(current.row() + 1);
            if (current.column() == 0) ui->loggerFileLocation->setText(settings_->getLoggerFileLocation(current.data().toString()));
        }
    );
    connect(ui->commonFileButton, &QPushButton::clicked, [this, sinks] {
        sinks->setCurrentIndex(0);
        ui->table->setCurrentIndex({});
        ui->loggerFileLocation->setText(settings_->getLoggerFileLocation());
    });
    connect(ui->openInEditorButton, &QPushButton::clicked, [this] {
        QDesktopServices::openUrl(QUrl::fromLocalFile(ui->loggerFileLocation->text()));
    });
}

LoggingToolSettingsWidget::~LoggingToolSettingsWidget() {
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
