#include "UIExporterToolSettingsWidget.h"

#include "Logger.h"
#include "ui_UIExporterToolSettingsWidget.h"

#define LOGGER_NAME "UI Exporter Settings"

using namespace UI;

UIExporterToolSettingsWidget::UIExporterToolSettingsWidget(UIExporterToolSettings &settings, QWidget *parent)
    : BaseExtensionsSettingsPageWidget(settings, parent),
      ui(new Ui::UIExporterToolSettingsWidget),
      settings(settings) {
    ui->setupUi(this);

    auto it = settings.begin();
    processOptions([&it, &settings](BaseUIExporterOptionsWidget* uiExporterOptionsWidget) {
            if (it == settings.end()) {
                LOG_WARN("Not all options are provided for UI Exporter Settings ({} will be disabled)", typeid(*uiExporterOptionsWidget).name());
                return;
            }
            uiExporterOptionsWidget->setOptions(*it++);
    });

    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::rootFolderChanged,
            ui->jsonUIExporterOptionsWidget, &JsonUIExporterOptionsWidget::rootFolderChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::fileNameChanged,
            ui->jsonUIExporterOptionsWidget, &JsonUIExporterOptionsWidget::fileNameChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::objectNameChanged,
            ui->jsonUIExporterOptionsWidget, &JsonUIExporterOptionsWidget::objectNameChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::classNameChanged,
            ui->jsonUIExporterOptionsWidget, &JsonUIExporterOptionsWidget::classNameChanged);

    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::rootFolderChanged,
            ui->xmlUIExporterOptionsWidget, &XmlUIExporterOptionsWidget::rootFolderChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::fileNameChanged,
            ui->xmlUIExporterOptionsWidget, &XmlUIExporterOptionsWidget::fileNameChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::objectNameChanged,
            ui->xmlUIExporterOptionsWidget, &XmlUIExporterOptionsWidget::objectNameChanged);
    connect(ui->generalUIExporterOptionsWidget, &GeneralUIExporterOptionsWidget::classNameChanged,
            ui->xmlUIExporterOptionsWidget, &XmlUIExporterOptionsWidget::classNameChanged);
}

UIExporterToolSettingsWidget::~UIExporterToolSettingsWidget() {
    delete ui;
}

void UIExporterToolSettingsWidget::save() {
        processOptions([this](BaseUIExporterOptionsWidget* optionsWidget) {
                settings.editSettings(optionsWidget->getTitle(), [optionsWidget](QSettings* settings) {
                        optionsWidget->write(settings);
                });
        });
}

void UIExporterToolSettingsWidget::reset() {
    settings.reset();
}

void UIExporterToolSettingsWidget::read() {
    processOptions([this](BaseUIExporterOptionsWidget* optionsWidget) {
            settings.editSettings(optionsWidget->getTitle(), [optionsWidget](QSettings* settings) {
                    optionsWidget->read(settings);
            });
    });
}

void UIExporterToolSettingsWidget::processOptions(const std::function<void(BaseUIExporterOptionsWidget*)>& processor) const {
        for (const auto uiExporterOptionsWidget: this->findChildren<BaseUIExporterOptionsWidget*>()) {
          processor(uiExporterOptionsWidget);
        }
}
