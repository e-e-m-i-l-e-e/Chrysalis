#include "TabularInput.h"

#include "ui_TabularInput.h"

using namespace CLO3D::UI;

TabularInput::TabularInput(QWidget *parent) : QWidget(parent), ui(new Ui::TabularInput) {
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->widget->setVisible(ui->expandButton->isChecked());
    // UTILITY_API->UpdateCloStyleForPlugIn(this);
}

TabularInput::~TabularInput() {
    delete ui;
}

QString TabularInput::getTitle() const {
    return ui->name->text();
}

void TabularInput::setTitle(const QString &title) const {
    ui->name->setText(title);
}