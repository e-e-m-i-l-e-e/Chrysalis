#include "TableInputAccordion.h"
#include "ui_TableInputAccordion.h"

#include <QPropertyAnimation>

using namespace UI;

TableInputAccordion::TableInputAccordion(QWidget *parent): BaseContainer(parent), ui(new Ui::TableInputAccordion) {
    ui->setupUi(this);
    ui->title->setProperty("widget-type", "Highlight");

    auto* animation = new QPropertyAnimation(ui->accordionContent, "maximumHeight");
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    ui->table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(ui->table->model(), &QAbstractItemModel::rowsInserted, this, &TableInputAccordion::updateTableHeight);
    connect(ui->table->model(), &QAbstractItemModel::rowsRemoved,  this, &TableInputAccordion::updateTableHeight);
    updateTableHeight();

    connect(ui->accordionTitle, &ClickableWidget::clicked, this, [this, animation] {
        const int contentHeight = ui->accordionContent->layout()->sizeHint().height();
        if (ui->accordionContent->maximumHeight() == 0) {
            animation->setStartValue(0);
            animation->setEndValue(contentHeight);
        } else {
            animation->setStartValue(contentHeight);
            animation->setEndValue(0);
        }
        animation->start();
    });
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
    updateTableHeight();
}

ClickableWidget* TableInputAccordion::getAccordionTitle() const {
    return ui->accordionTitle;
}

void TableInputAccordion::updateTableHeight() const {
    int h = ui->table->horizontalHeader()->height() + ui->table->frameWidth() * 2;
    for (int i = 0; i < ui->table->rowCount(); i++) {
        h += ui->table->rowHeight(i);
    }
    ui->table->setFixedHeight(h);
}
