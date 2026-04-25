#include "BaseUIExporterSettingsBlockContainerWidget.h"
#include "ui_BaseUIExporterSettingsBlockContainerWidget.h"

#include <QGraphicsOpacityEffect>

using namespace UI;

BaseUIExporterSettingsBlockContainerWidget::BaseUIExporterSettingsBlockContainerWidget(QWidget *parent)
    : NamedWidget(parent), ui(new Ui::BaseUIExporterSettingsBlockContainerWidget) {
    ui->setupUi(this);
    ui->settingsBlockContainerWidget->install({ui->customTools, ui->settingsBlockContent});
    connect(ui->rootFolder, &QLineEdit::textChanged, this, &BaseUIExporterSettingsBlockContainerWidget::rootFolderChanged);
    connect(ui->fileName, &QLineEdit::textChanged, this, &BaseUIExporterSettingsBlockContainerWidget::fileNameChanged);
    connect(ui->objectName, &QLineEdit::textChanged, this, &BaseUIExporterSettingsBlockContainerWidget::objectNameChanged);
    connect(ui->className, &QLineEdit::textChanged, this, &BaseUIExporterSettingsBlockContainerWidget::classNameChanged);
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
    else if (index == 2) {
        ui->settingsWrapper->addWidget(widget, 1, 1);
        setLabelWidth(labelWidth_);
        for (const auto toolButton: this->findChildren<QToolButton*>()) {
            const auto effect = new QGraphicsOpacityEffect(this);
            effect->setOpacity(1);
            toolButton->setGraphicsEffect(effect);
        }
    }
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

void BaseUIExporterSettingsBlockContainerWidget::enableContent(const bool isEnabled) const {
    ui->settingsBlockContent->setEnabled(isEnabled);
    const float opacity = isEnabled ? 1 : 0.5;
    for (const auto toolButton: this->findChildren<QToolButton*>()) {
        if (const auto effect = qobject_cast<QGraphicsOpacityEffect*>(toolButton->graphicsEffect())) {
            effect->setOpacity(opacity);
        }
    }
}

void BaseUIExporterSettingsBlockContainerWidget::setRootFolder(const QString &rootFolder) const {
    ui->rootFolder->setText(rootFolder);
}

void BaseUIExporterSettingsBlockContainerWidget::setFileName(const QString &fileName) const {
    ui->fileName->setText(fileName);
}

void BaseUIExporterSettingsBlockContainerWidget::setObjectName(const QString &objectName) const {
    ui->objectName->setText(objectName);
}

void BaseUIExporterSettingsBlockContainerWidget::setClassName(const QString &className) const {
    ui->className->setText(className);
}
