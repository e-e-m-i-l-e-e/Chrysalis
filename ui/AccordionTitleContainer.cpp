#include "AccordionTitleContainer.h"
#include "ui_AccordionTitleContainer.h"

using namespace UI;

AccordionTitleContainer::AccordionTitleContainer(QWidget *parent) : QWidget(parent),
                                                                    ui(new Ui::AccordionTitleContainer) {
    ui->setupUi(this);
}

AccordionTitleContainer::~AccordionTitleContainer() {
    delete ui;
}

QString AccordionTitleContainer::getTitle() const {
    return ui->title->text();
}

void AccordionTitleContainer::setTitle(const QString& title) const {
    ui->title->setText(title);
}

void AccordionTitleContainer::setCustomWidget(QWidget *widget) const {
    ui->horizontalLayout->addWidget(widget);
    // if (auto* customWidget = getCustomWidget()) {
    //     ui->horizontalLayout->replaceWidget(customWidget, widget);
    // } else ui->horizontalLayout->addWidget(widget);
}

QWidget * AccordionTitleContainer::getCustomWidget() const {
    const auto widget = new QWidget();
    widget->setObjectName("customWidget");
    return widget;
}
