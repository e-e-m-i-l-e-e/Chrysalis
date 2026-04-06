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

QLayout* AccordionContainer::getLayout(const int index) {
    switch (index) {
        case 0:
            return ui->titleLayout;
        case 1:
            return ui->contentLayout;
        default:
            return nullptr;
    }
}
