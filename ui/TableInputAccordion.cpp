#include "TableInputAccordion.h"
#include "ui_TableInputAccordion.h"

using namespace UI;

TableInputAccordion::TableInputAccordion(QWidget *parent) : Container(parent), ui(new Ui::TableInputAccordion) {
    ui->setupUi(this);
}

TableInputAccordion::~TableInputAccordion() {
    delete ui;
}

void TableInputAccordion::insertWidget(const int index, QWidget *widget) {
    if (index == 0) ui->titleLayout->insertWidget(2, widget);
    else if (index == 1) ui->contentLayout->insertWidget(0, widget);
    else ui->contentLayout->insertWidget(2, widget);
}

QWidget* TableInputAccordion::getWidget(const int index) {
    if (index == 0) return ui->titleLayout->itemAt(2)->widget();
    if (index == 1) return ui->contentLayout->itemAt(0)->widget();
    return ui->contentLayout->itemAt(2)->widget();
}

QBoxLayout* TableInputAccordion::getLayout() {
    return ui->verticalLayout;
}

QString TableInputAccordion::getTitle() const {
    return ui->title->text();
}

void TableInputAccordion::setTitle(const QString &title) const {
    ui->title->setText(title);
}

QStringList TableInputAccordion::getColumns() const {
    QStringList columns {};
    for (int i = 0; i < ui->table->columnCount(); i++) {
        columns << ui->table->horizontalHeaderItem(i)->text();
    }
    return columns;
}

void TableInputAccordion::setColumns(const QStringList &columns) const {
    ui->table->clear();
    ui->table->setColumnCount(columns.size());
    ui->table->setHorizontalHeaderLabels(columns);
}
