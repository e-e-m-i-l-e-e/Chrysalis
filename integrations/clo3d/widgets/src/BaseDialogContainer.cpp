#include "BaseDialogContainer.h"
#include "ui_BaseDialogContainer.h"

using namespace UI;

BaseDialogContainer::BaseDialogContainer(QWidget* parent)
    : QDialog(parent), ui(new Ui::BaseDialogContainer) {
    ui->setupUi(this);
}

BaseDialogContainer::~BaseDialogContainer() {
    delete ui;
}

int BaseDialogContainer::count() const {
    return 2;
}

void BaseDialogContainer::insertWidget(int index, QWidget* widget) {
    if (index == 0) ui->contentWidget->layout()->addWidget(widget);
    else ui->footerLayout->layout()->addWidget(widget);
}

QWidget* BaseDialogContainer::getWidget(int index) {
    if (index == 0) return ui->contentWidget->layout()->itemAt(0)->widget();
    return ui->footerLayout->itemAt(0)->widget();
}
