#include "BaseUIExporterSettingsBlockContainerWidget.h"
#include "ui_BaseUIExporterSettingsBlockContainerWidget.h"

using namespace UI;

BaseUIExporterSettingsBlockContainerWidget::BaseUIExporterSettingsBlockContainerWidget(QWidget *parent)
    : NamedWidget(parent), ui(new Ui::BaseUIExporterSettingsBlockContainerWidget) {
    ui->setupUi(this);
    ui->settingsBlockContainerWidget->install({ui->customTools, ui->settingsBlockContent});
}

BaseUIExporterSettingsBlockContainerWidget::~BaseUIExporterSettingsBlockContainerWidget() {
    delete ui;
}

int BaseUIExporterSettingsBlockContainerWidget::count() const {
    return 3;
}

void BaseUIExporterSettingsBlockContainerWidget::insertWidget(int index, QWidget *widget) {
    if (index == 0) ui->customToolsWrapper->layout()->addWidget(widget);
    else if (index == 1) ui->settingsWrapper->addWidget(widget, 1, 0);
    else if (index == 2) ui->settingsWrapper->addWidget(widget, 1, 1);
}

QWidget* BaseUIExporterSettingsBlockContainerWidget::getWidget(int index) {
    if (index == 0) return ui->customToolsWrapper->layout()->itemAt(0)->widget();
    if (index == 1) return ui->settingsWrapper->layout()->itemAt(2)->widget();
    if (index == 2) return ui->settingsWrapper->layout()->itemAt(3)->widget();
    return nullptr;
}

void BaseUIExporterSettingsBlockContainerWidget::setTitle(const QString &title) {
    NamedWidget::setTitle(title);
    ui->settingsBlockContainerWidget->setTitle(title);
}

int BaseUIExporterSettingsBlockContainerWidget::getLabelWidth() const {
    return labelWidth_;
}

void BaseUIExporterSettingsBlockContainerWidget::setLabelWidth(const int labelWidth) {
    labelWidth_ = labelWidth;
    for (const auto label: ui->settingsBlockContent->findChildren<QLabel*>()) {
        label->setFixedWidth(std::max(labelWidth, label->sizeHint().width()));
    }
}
