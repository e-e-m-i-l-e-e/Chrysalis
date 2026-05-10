#include "LoggingToolSettingsWidget.h"
#include "ui_LoggingToolSettingsWidget.h"

#include <QComboBox>

using namespace UI;

LoggingToolSettingsWidget::LoggingToolSettingsWidget(LoggingToolSettings* settings, QWidget *parent)
: BaseExtensionSettingsWidget(settings, parent), ui(new Ui::LoggingToolSettingsWidget), settings_(settings) {
    ui->setupUi(this);
    const int lastColumn = ui->table->columnCount() - 1;
    QHeaderView *header = ui->table->horizontalHeader();
    for (int i = 0; i < lastColumn; i++) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    header->setSectionResizeMode(lastColumn, QHeaderView::ResizeToContents);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);
    for (const auto [loggers, levels] = settings_->getEntries();
         const auto& [name, currentLevel]: loggers) {
        const int row = ui->table->rowCount();
        ui->table->insertRow(row);

        // auto *label = new QLabel(name);
        // // label->setAttribute(Qt::WA_TransparentForMouseEvents); // ignores clicks
        // label->setStyleSheet("padding-left: 2px;"); // optional style
        // ui->table->setCellWidget(row, 0, label);

        QTableWidgetItem *item = new QTableWidgetItem(name);
        // item->setFlags(Qt::NoItemFlags);
        // item->setFlags(Qt::ItemIsEditable);
        ui->table->setItem(row, 0, item);
        // ui->table->setItem(row, 0, new QTableWidgetItem(name));
        auto *combo = new QComboBox(ui->table);
        for (const auto& level: levels) {
            combo->addItem(level);
        }
        combo->setCurrentIndex(currentLevel);
        ui->table->setCellWidget(row, 1, combo);
        ui->table->item(row, 0)->setFlags(ui->table->item(row, 0)->flags() & ~Qt::ItemIsSelectable);
    }
}

LoggingToolSettingsWidget::~LoggingToolSettingsWidget() {
    delete ui;
}