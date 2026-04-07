#include "AccordionContainer.h"

#include "ui_AccordionContainer.h"

using namespace UI;

AccordionContainer::AccordionContainer(QWidget *parent)
    : Container(parent),
      ui(new Ui::AccordionContainer) {
    ui->setupUi(this);
}

AccordionContainer::~AccordionContainer() {
    delete ui;
}

QBoxLayout* AccordionContainer::getLayout() {
    return ui->verticalLayout;
}
