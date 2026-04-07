#include "AccordionTitleContainer.h"
#include "ui_AccordionTitleContainer.h"

#include <QHBoxLayout>

using namespace UI;

AccordionTitleContainer::AccordionTitleContainer(QWidget *parent)
    : Container(parent),
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

QBoxLayout* AccordionTitleContainer::getLayout() {
    return ui->horizontalLayout;
}
