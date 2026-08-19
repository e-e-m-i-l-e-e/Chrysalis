#include "BaseDialogContainer.h"

#include <QLineEdit>

#include "ui_BaseDialogContainer.h"

using namespace CLO3D::UI;

BaseDialogContainer::BaseDialogContainer(QWidget* parent)
    : NamedWidget(parent), ui(new Ui::BaseDialogContainer) {
    ui->setupUi(this);
    connect(this, &NamedWidget::titleChanged, ui->label, &QLabel::setText);
    connect(ui->close, &QToolButton::clicked, this, &BaseDialogContainer::closed);
}

BaseDialogContainer::~BaseDialogContainer() {
    delete ui;
}

int BaseDialogContainer::count() const {
    return 2;
}

void BaseDialogContainer::insertWidget(int index, QWidget* widget) {
    if (index == 0) ui->contentLayout->addWidget(widget);
    else ui->customFooter->layout()->addWidget(widget);
}

QWidget* BaseDialogContainer::getWidget(int index) {
    if (index == 0) return ui->contentLayout->itemAt(0)->widget();
    return ui->customFooter->layout()->itemAt(0)->widget();
}
