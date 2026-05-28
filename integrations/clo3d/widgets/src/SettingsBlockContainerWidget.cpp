#include "SettingsBlockContainerWidget.h"
#include "ui_SettingsBlockContainerWidget.h"

using namespace  UI;

SettingsBlockContainerWidget::SettingsBlockContainerWidget(QWidget *parent)
    : NamedWidget(parent), BaseContainer(), ui(new Ui::SettingsBlockContainerWidget) {
    ui->setupUi(this);
}

SettingsBlockContainerWidget::~SettingsBlockContainerWidget() {
    delete ui;
}

int SettingsBlockContainerWidget::count() const {
    return 2;
}

void SettingsBlockContainerWidget::insertWidget(int index, QWidget *widget) {
    if (index == 0) ui->customToolsWrapper->layout()->addWidget(widget);
    else if (index == 1) ui->settingsBlockContentWrapper->layout()->addWidget(widget);
}

QWidget* SettingsBlockContainerWidget::getWidget(int index) {
    switch (index) {
        case 0:
            return ui->customToolsWrapper->layout()->itemAt(0)->widget();
        case 1:
            return ui->settingsBlockContentWrapper->layout()->itemAt(0)->widget();
        default:
            return nullptr;
    }
}

void SettingsBlockContainerWidget::setTitle(const QString &title) {
    NamedWidget::setTitle(title);
    ui->label->setText("<img src=':/Resources/CommonIcon/Title Bullet Secondary.svg' width='11' height='11'>" + title);
}
