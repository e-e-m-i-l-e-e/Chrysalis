#include "AccordionTitleContainer.h"
#include "ui_AccordionTitleContainer.h"

using namespace UI;

AccordionTitleContainer::AccordionTitleContainer(QWidget *parent) : QWidget(parent),
                                                                    ui(new Ui::AccordionTitleContainer) {
    ui->setupUi(this);
    customWidget_ = new QWidget(this);
    customWidget_->setObjectName("customWidget");
    ui->horizontalLayout->addWidget(customWidget_);
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

void AccordionTitleContainer::setCustomWidget(QWidget *widget) {
    if (customWidget_) {
        ui->horizontalLayout->replaceWidget(customWidget_, widget);
        customWidget_->deleteLater();
    } else {
        ui->horizontalLayout->addWidget(widget);
    }
    widget->setParent(this);
    customWidget_ = widget;
}

QWidget * AccordionTitleContainer::getCustomWidget() const {
    return customWidget_;
}
