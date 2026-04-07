#include "TableContentContainer.h"
#include "ui_TableContentContainer.h"

using namespace UI;

TableContentContainer::TableContentContainer(QWidget *parent) : Container(parent), ui(new Ui::TableContentContainer) {
    ui->setupUi(this);
}

TableContentContainer::~TableContentContainer() {
    delete ui;
}

QStringList TableContentContainer::getColumns() const {
    QStringList columns {};
    for (int i = 0; i < ui->table->columnCount(); i++) {
        columns << ui->table->horizontalHeaderItem(i)->text();
    }
    return columns;
}

void TableContentContainer::setColumns(const QStringList& columns) const {
    ui->table->clear();
    ui->table->setColumnCount(columns.size());
    ui->table->setHorizontalHeaderLabels(columns);
}

QLayout* TableContentContainer::getLayout() {
    return ui->verticalLayout;
}
